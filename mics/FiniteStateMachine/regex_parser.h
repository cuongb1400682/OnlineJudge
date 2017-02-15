#ifndef REGEX_PARSER_H
#define REGEX_PARSER_H

#include <string.h>
#include <stdlib.h>
#include <stack>

using std::stack;

#define TERM_CHAR 255

struct ParseTreeNode {
  ParseTreeNode(char exp = 0) {
    this->exp = exp;
    left = right = NULL;
  }
  char exp;
  ParseTreeNode *left, *right;
};

class ParseTree {
 public:
  ParseTree() {
    root = NULL;
    regex = NULL;
    n = 0;
  }
  
  ParseTree(const char *regex) {
    int n_buff = 0;
    int n = strlen(regex);
    char *buff = new char[2 * n + 2];

    buff[n_buff++] = '(';

    for (int i = 0; i < n; i++) {
      buff[n_buff++] = regex[i];
      if (regex[i] == '*')
        buff[n_buff++] = TERM_CHAR;
      // consider the four cases: A.A -- A.(A) -- (A).A -- (A).(A)
      if (!isOperator(buff[n_buff - 1])) {
        if (!isOperator(regex[i + 1]) || regex[i + 1] == '(')
          buff[n_buff++] = '.';
      } else if (buff[n_buff - 1] == ')') {
        if (!isOperator(regex[i + 1]) || regex[i + 1] == '(')
          buff[n_buff++] = '.';
      }
    }

    buff[n_buff - 1] = ')';
    buff[n_buff] = '\0';

    this->regex = buff;
    this->n = n_buff ;
    this->root = NULL;
  }
  
  ~ParseTree() {
    if (this->regex)
      delete[] this->regex;
    if (this->root)
      destroyTree(this->root);
    this->regex = NULL;
    this->root = NULL;
  }

  /* These functions are deprecated. Uncomment them when needed */
  /*  void debug(ParseTreeNode *p, string indent="") {
    printf("%s(%c)\n", indent.c_str(), p->exp);
    if (p->left)
      debug(p->left, indent+"   .");
    if (p->right)
      debug(p->right, indent+"   .");    
      }

  void debug() {
    debug(root);
  }
  */

  void parse() {
    int *partner = new int[this->n];
    matchParentheses(regex, n, partner);
    this->root = parseRegex(this->regex, 0, this->n - 1, partner);
    delete[] partner;
  }

  ParseTreeNode *getRoot() {
    return this->root;
  }

 private:
  ParseTreeNode *root;
  char *regex;
  int n;

  ParseTreeNode *parseRegex(const char *regex, int L, int R, int *partner) {
    stack<ParseTreeNode *> term;
    stack<ParseTreeNode *> op;
    ParseTreeNode *node;

    for (int i = L; i <= R; i++) {
      if (regex[i] == '(') {
        term.push(parseRegex(regex, i + 1, partner[i] - 1, partner));
        i = partner[i];
      } else if (!isOperator(regex[i])) {
        term.push(new ParseTreeNode(regex[i]));
      } else {
        while (!op.empty()) {
          if (priority(op.top()->exp) < priority(regex[i]))
            break;
          // get the operator
          node = op.top();
          op.pop();
          // connect first item in term to node's right
          node->right = term.top();
          term.pop();
          // connect second item in term to node's left
          node->left = term.top();
          term.pop();
          // push the new node to term
          term.push(node);
        }
        op.push(new ParseTreeNode(regex[i]));
      }
    }

    while (!op.empty()) {
      // get the operator
      node = op.top();
      op.pop();
      // connect first item in term to node's right
      node->right = term.top();
      term.pop();
      // connect second item in term to node's left
      node->left = term.top();
      term.pop();
      // push the new node to term
      term.push(node);
    }

    return term.empty() ? NULL : term.top();
  }

  int priority(char c) {
    if (c == '*')
      return 2;
    if (c == '.')
      return 1;
    if (c == '|')
      return 0;
  }
  
  bool isOperator(char c) {
    return c == '|' || c == '*' || c == '(' || c == ')' || c == '.';
  }

  void destroyTree(ParseTreeNode *p) {
    if (p->left)
      destroyTree(p->left);
    if (p->right)
      destroyTree(p->right);
    delete p;
  }

  void matchParentheses(char *regex, int n, int *partner) {
    memset(partner, -1, n * sizeof(partner[0]));

    stack<int> parens;
    for (char *p = regex; *p; p++)
      if (*p == '(')
        parens.push(p - regex);
      else if (*p == ')') {
        partner[p - regex] = parens.top();
        partner[parens.top()] = p - regex;
        parens.pop();
      }  
  }
};

#endif



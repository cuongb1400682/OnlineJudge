#ifndef FSM_H
#define FSM_H

#include "regex_parser.h"
#include <set>
#include <queue>

using std::set;
using std::pair;
using std::make_pair;
using std::swap;
using std::queue;

struct FSMState {
  bool isFinalState;
  set<pair<FSMState *, int> > adjSet;

  FSMState() {
    isFinalState = false;
    adjSet.clear();
  }

  ~FSMState() {
    adjSet.clear();
  }

  void connect(FSMState *state, int input) {
    adjSet.insert(make_pair(state, input));
  }
};

class FiniteStateMachine {
public:
  FiniteStateMachine() {
    startState = NULL;
    states.clear();
  }

  FiniteStateMachine(const char *regex) {
    ParseTree parser(regex);
    states.clear();
    parser.parse();
    startState = constructFSM(parser.getRoot());
    minimizeDFA();
  }

  ~FiniteStateMachine() {
    set<FSMState *>::iterator it;
    for (it = states.begin(); it != states.end(); it++)
      delete (*it);
    states.clear();
    startState = NULL;
  }

  FSMState *getStartState() {
    return startState;
  }

  bool match(const char *str) {
    queue<pair<FSMState *, int> > q;
    set<pair<FSMState *, int> >::iterator it;
    FSMState *currentState, *nextState;
    int lenOfStr = strlen(str);
    int currentLen;
    char nextChar;

    q.push(make_pair(startState, 0));

    while (!q.empty()) {
      currentState = q.front().first;
      currentLen = q.front().second;
      q.pop();

      if (currentLen == lenOfStr && currentState->isFinalState)
        return true;

      for (it = currentState->adjSet.begin();
           it != currentState->adjSet.end(); it++) {
        nextState = it->first;
        nextChar = it->second;
        if (str[currentLen] == nextChar)
          q.push(make_pair(nextState, currentLen + 1));
      }
    }

    return false;
  }

private:
  FSMState *startState;
  set<FSMState *> states;

  /* This function is left for further researching */
  void minimizeDFA() {
    // refer wikipedia: https://en.wikipedia.org/wiki/DFA_minimization
    // for more information about this problem.
    // I will not solve this, because my objective of
    // designing this class is just to illustrate the
    // way of constructing Deterministic Finite Automaton.
    // This function will be empty.
  }

  /* This function is deprecated. Uncomment it when needed */
  /*  
  void debug(bool isPrintPointer = true) {
    set<FSMState *>::iterator it;
    set<pair<FSMState *, int> >::iterator jt;
    map<FSMState *, int> label;
    int cnt = 0;

    for (it = states.begin(); it != states.end(); it++)
      label[*it] = cnt++;

    for (it = states.begin(); it != states.end(); it++) {
      for (jt = (*it)->adjSet.begin();
           jt != (*it)->adjSet.end(); jt++) {
        FSMState *u = *it;
        FSMState *v = jt->first;
        if (isPrintPointer) {
          printf(u->isFinalState ? "[%p], " : "%p, ", u);
          printf(v->isFinalState ? "[%p], " : "%p, ", v);
          printf("%c\n",  jt->second);
        } else {
          printf(u->isFinalState ? "[%d], " : "%d, ", label[u]);
          printf(v->isFinalState ? "[%d], " : "%d, ", label[v]);
          printf("%c\n",  jt->second);
        }
      }
    }

    printf("start state = ");
    if (isPrintPointer)
      printf(startState->isFinalState ? "[%p], " : "%p, ", startState);
    else
      printf(startState->isFinalState ? "[%d], " : "%d, ", label[startState]);
      }
  */

  FSMState *newFSMState() {
    FSMState *newState = new FSMState();
    states.insert(newState);
    return newState;
  }

  FSMState *generateBaseCase(char chr) {
    FSMState *p1 = newFSMState();
    FSMState *p2 = newFSMState();
    p1->connect(p2, chr);
    p2->isFinalState = true;
    return p1;
  }

  void enumerateFinalState(FSMState *u,
                           set<FSMState *> &lst,
                           set<FSMState *> &visted) {
    if (visted.count(u) > 0)
      return;
    visted.insert(u);
    if (u->isFinalState)
      lst.insert(u);
    set<pair<FSMState *,int > >::iterator it;
    for (it = u->adjSet.begin(); it != u->adjSet.end(); it++)
      enumerateFinalState(it->first, lst, visted);
  }

  void enumerateFinalStateAndNextToIt(FSMState *s1,
                                      set<FSMState *> &finalStates,
                                      set<pair<FSMState *, int> > &nextToFinal,
                                      set<FSMState *> &visted) {
    if (visted.count(s1) > 0)
      return;
    visted.insert(s1);
    set<pair<FSMState *,int > >::iterator it;
    for (it = s1->adjSet.begin(); it != s1->adjSet.end(); it++) {
      FSMState *u = s1;
      FSMState *v = it->first;
      int weight = it->second;
      if (v->isFinalState) {
        finalStates.insert(v);
        nextToFinal.insert(make_pair(u, weight));
      }
      enumerateFinalStateAndNextToIt(v, finalStates,
                                     nextToFinal, visted);
    }    
  }

  FSMState *dotOperator(FSMState *s1, FSMState *s2) {
    set<pair<FSMState *, int> > nextToFinal;
    set<FSMState *> finalStates, visted;    
    set<FSMState *>::iterator it;
    set<pair<FSMState *, int> >::iterator jt;
    bool isFinalState = s1->isFinalState && s2->isFinalState;

    enumerateFinalStateAndNextToIt(s1, finalStates,
                                   nextToFinal, visted);

    // remove all final states in Fa
    for (it = finalStates.begin(); it != finalStates.end(); it++)
      (*it)->isFinalState = false;

    // add transitions from next to final in Ma to sb
    for (jt = nextToFinal.begin(); jt != nextToFinal.end(); jt++)
      jt->first->connect(s2, jt->second);
    
    if (s1->isFinalState) {
      // add transitions from sa to states which are adjacent to sb
      for (jt = s2->adjSet.begin(); jt != s2->adjSet.end(); jt++)
        s1->connect(jt->first, jt->second);      
    }
    
    s1->isFinalState = isFinalState;
    return s1;
  }

  FSMState *barOperator(FSMState *s1, FSMState *s2) {
    FSMState *newFinalState;
    set<pair<FSMState *, int> >::iterator it;
    
    newFinalState = newFSMState();
    newFinalState->isFinalState = s1->isFinalState || s2->isFinalState;

    for (it = s1->adjSet.begin(); it != s1->adjSet.end(); it++)
      newFinalState->connect(it->first, it->second);

    for (it = s2->adjSet.begin(); it != s2->adjSet.end(); it++)
      newFinalState->connect(it->first, it->second);

    return newFinalState;
  }

  FSMState *starOperator(FSMState *s) {
    set<FSMState *> finalStates;
    set<pair<FSMState *, int> >::iterator it;
    set<FSMState *>::iterator jt;
    set<FSMState *> visted;
    FSMState *newFinalState;

    // create a new state, it is the new start state
    newFinalState = newFSMState();
    // set all final state of the machine
    enumerateFinalState(s, finalStates, visted);
    // the new start state is also final state
    finalStates.insert(newFinalState);
    newFinalState->isFinalState = true;

    // (finalState, stateAdjToSa)
    for (it = s->adjSet.begin(); it != s->adjSet.end(); it++)
      for (jt = finalStates.begin(); jt != finalStates.end(); jt++)
        (*jt)->connect(it->first, it->second);

    return newFinalState;
  }
  
  FSMState *constructFSM(ParseTreeNode *p) {
    if (p->left == NULL && p->right == NULL) {
      if ((int) p->exp == -1)
        return NULL;
      else
        return generateBaseCase(p->exp);
    } else {
      FSMState *sA = constructFSM(p->left);
      FSMState *sB = constructFSM(p->right);
      if (sA == NULL)
        swap(sA, sB);
      if (p->exp == '.')
        return dotOperator(sA, sB);
      else if (p->exp == '|')
        return barOperator(sA, sB);
      else if (p->exp == '*')
        return starOperator(sA);
    }
  }
};

#endif





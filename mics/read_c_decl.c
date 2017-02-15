#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE         1
#define FALSE        0
#define MAX_TOKEN   10

enum {
    OPERATOR,
    NUMERIC,
    USRDFN,
    QUALIFIER,
    TYPE
};

const char *strtyp[] = { "operator", "numeric",
                         "user defined", "qualifier",
                         "data type" };

struct __token_t {
    char tok[MAX_TOKEN];
    int  tok_typ;
    struct __token_t * next;
    struct __token_t * prev;
};

typedef struct __token_t token_t;

/* function prototypes */
token_t * next_token    (token_t *token);
int       is_operator   (int c);
int       is_qualifier  (const char *token);
int       is_datatype   (const char *token);
int       token_type    (const char *token);
token_t * initialize    (void);
void      englishization(token_t *tok);
token_t * unscramble_caret   (token_t *p);
token_t * unscramble_qualifier     (token_t *p);
token_t * kill_left     (token_t *p);
token_t * kill_right    (token_t *p);
void      swap          (token_t *a, token_t *b);

int main(void) {
    token_t *top;
    top = initialize();
    englishization(top);
    printf("\n");
    return 0;
}

token_t * kill_left(token_t *p) {
    token_t *t = p;
    if (p->prev) p->prev->next = p->next;
    if (p->next) p->next->prev = p->prev;
    p = p->prev;
    free(t);
      return p;
}

token_t * kill_right(token_t *p) {
    token_t *t = p;
    if (p->prev) p->prev->next = p->next;
    if (p->next) p->next->prev = p->prev;
    p = p->next;
    free(t);
    return p;
}

token_t *unscramble_caret(token_t *p) {
    while (p->tok[0] == '[') {
        p = kill_right(p);
        printf(" array[%s] of", p->tok_typ == NUMERIC ? p->tok : "");
        if (p->tok_typ == NUMERIC) p = kill_right(p);
        p = kill_right(p);
    }

    while (p->tok[0] == '(') {
        p = kill_right(p);
        printf(" function returning");
        while (p->tok[0] != ')')
            p = kill_right(p);
        p = kill_right(p);
    }
    return p;
}

token_t *unscramble_qualifier(token_t *p) {
    while (p->tok_typ == QUALIFIER) {
        if (p->tok[0] == '*')
            printf(" pointer to");
        else if (strcmp(p->tok, "const") == 0)
            printf(" read-only");
        else if (strcmp(p->tok, "volatile") == 0)
            printf(" volatile");
        p = kill_left(p);
    }
    return p;
}

void swap(token_t *a, token_t *b) {
    char buf[MAX_TOKEN];
    int  type;

    strcpy(buf, a->tok);
    strcpy(a->tok, b->tok);
    strcpy(b->tok, buf);

    type = a->tok_typ;
    a->tok_typ = b->tok_typ;
    b->tok_typ = type;
}

void englishization(token_t *tok) {
    token_t *p = NULL;
    char stype[100] = { 0 };
    while (tok) {
        if (tok->tok_typ == USRDFN)
            p = tok;
        tok = tok->prev;
    }

    printf("%s is", p->tok);
    p = kill_right(p);

    while (p && p->tok_typ != TYPE) {
        p = unscramble_caret(p);
        p = unscramble_qualifier(p->prev);
        if (p->tok[0] == '(') {
            p = kill_right(p);
            p = kill_right(p);
        }
    }

    while (p->next)
        p = kill_left(p->next);

    while (p) {
        strcat(stype, " ");
        strcat(stype, p->tok);
        p = kill_left(p);
    }

    printf("%s", stype);
}

token_t * initialize(void) {
    token_t *top = NULL;
    token_t *result;

    while ((top = next_token(top)) != NULL) {
        result = top;
    }

    for (top = result; top != NULL; top = top->prev) {
        if (top->tok_typ == TYPE && top->prev)
            if (top->prev->tok_typ == TYPE || top->prev->tok_typ == QUALIFIER)
                swap(top, top->prev);
    }
    return result;
}

token_t * next_token(token_t *token) {
    int  c, tok_len;
    char tokbuf[MAX_TOKEN];
    token_t * result;

    memset(tokbuf, 0, sizeof(tokbuf));
    tok_len = 0;
    result  = NULL;

    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            ungetc(c, stdin);
            while ((c = getchar()) != EOF && isalpha(c))
                tokbuf[tok_len++] = c;
            tokbuf[tok_len] = '\0';
            if (c != EOF) ungetc(c, stdin);
        } else if (isdigit(c)) {
            ungetc(c, stdin);
            while ((c = getchar()) != EOF && isdigit(c))
                tokbuf[tok_len++] = c;
            tokbuf[tok_len] = '\0';
            if (c != EOF) ungetc(c, stdin);
        } else if (is_operator(c) || c == '*') {
            tokbuf[0] = c;
            tokbuf[1] = '\0';
            tok_len   = 1;
        }

        if (tok_len) {
            result = (token_t *) malloc(sizeof(token_t));
            strcpy(result->tok, tokbuf);
            result->tok_typ = token_type(tokbuf);
            result->prev = token;
            result->next = NULL;
            if (token) token->next = result;
            break;
        }
    }
    return result;
}

int is_operator(int c) {
    return c == '(' || c == ')' || c == '[' ||
           c == ']' || c == ';' || c == ',';
}

int is_qualifier(const char *token) {
    int i;
    static const char *qualifier[] = { "const", "volatile", "*" };
    for (i = 0; i < 3; ++i)
        if (strcmp(qualifier[i], token) == 0)
            break;
    return i < 3;
}

int is_datatype (const char *token) {
    int i;
    static const char *data_type[] = { "int", "long", "short", "float",
                                "double", "signed", "unsigned",
                                "char", "void" };
    for (i = 0; i < 9; ++i)
        if (strcmp(data_type[i], token) == 0)
            break;
    return i < 9;
}

int token_type(const char *token) {
    if (is_datatype(token))
        return TYPE;
    else if (is_operator(token[0]))
        return OPERATOR;
    else if (is_qualifier(token))
        return QUALIFIER;
    else if (isdigit(token[0]))
        return NUMERIC;
    else
        return USRDFN;
}


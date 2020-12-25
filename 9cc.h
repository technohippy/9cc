#include <stdbool.h>

void error_at(char *loc, char *fmt, ...);
void error(char *fmt, ...);

typedef enum {
  TK_RESERVED,
  TK_NUM,
  TK_EOF,
} TokenKind;

typedef struct Token Token;

struct Token {
  TokenKind kind;
  Token *next;
  int val;
  char *str;
  int len;
};

Token *new_token(TokenKind kind, Token *cur, char *str, int len);
Token *tokenize(char *p);

bool consume(char *op);
void expect(char *op);
int expect_number();
bool at_eof();

typedef enum {
  ND_EQ,
  ND_NEQ,
  ND_LT,
  ND_LE,
  ND_ADD,
  ND_SUB,
  ND_MUL,
  ND_DIV,
  ND_NUM,
} NodeKind;

typedef struct Node Node;

struct Node {
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val;
};

Node *new_node(NodeKind kind, Node *lhs, Node *rhs);
Node *new_node_num(int val);

// expr = equality
// equality = relational ("+" relational | "-" relational)*
// relational = add ("<" add | "<=" add | ">" add | ">=" add)*
// add = mul ("*" mul | "/" mul)*
// mul = unary ("*" unary | "/" unary)*
// unary   = ("+" | "-")? primary
// primary = num | "(" expr ")"
Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

void gen(Node *node);
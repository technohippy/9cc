#include <stdbool.h>

void error_at(char *loc, char *fmt, ...);
void error(char *fmt, ...);

typedef enum {
  TK_RESERVED,
  TK_IDENT,
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
Token *tokenize();

bool consume(char *op);
Token *consume_ident();
void expect(char *op);
int expect_number();
bool at_eof();

typedef enum {
  ND_EQ,     // 0
  ND_NEQ,    // 1
  ND_LT,     // 2
  ND_LE,     // 3
  ND_ADD,    // 4
  ND_SUB,    // 5
  ND_MUL,    // 6
  ND_DIV,    // 7
  ND_NUM,    // 8
  ND_ASSIGN, // 9
  ND_LVAR,   // 10
} NodeKind;

typedef struct Node Node;

struct Node {
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val; // for num
  int offset; // for lvar
};

Node *new_node(NodeKind kind, Node *lhs, Node *rhs);
Node *new_node_num(int val);

// program = stmt*
// stmt = expr ";"
// expr = assign
// assign = equality ("=" assign)?
// equality = relational ("+" relational | "-" relational)*
// relational = add ("<" add | "<=" add | ">" add | ">=" add)*
// add = mul ("*" mul | "/" mul)*
// mul = unary ("*" unary | "/" unary)*
// unary   = ("+" | "-")? primary
// primary = num | "(" expr ")"
void program();
Node *stmt();
Node *expr();
Node *assign();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

void gen(Node *node);

typedef struct LVar LVar;

struct LVar {
  LVar *next;
  char *name;
  int len;
  int offset;
};

LVar *locals;

LVar *find_lvar(Token *tok);

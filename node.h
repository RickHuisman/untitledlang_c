#ifndef UNTITLEDLANG_NODE_H
#define UNTITLEDLANG_NODE_H

typedef struct Node Node;
typedef struct BinaryExpr BinaryExpr;
typedef struct LetAssign LetAssign;
typedef struct LetSet LetSet;
typedef struct LetGet LetGet;

typedef enum {
  UNARY_NEGATE,
} UnaryOperator;

typedef enum {
  BIN_ADD,
  BIN_SUBTRACT,
  BIN_MULTIPLY,
  BIN_DIVIDE,
} BinaryOperator;

typedef enum {
  NODE_UNARY,
  NODE_BINARY,
  NODE_LET_ASSIGN,
  NODE_LET_SET,
  NODE_LET_GET,
  NODE_BLOCK,
  NODE_NUMBER,
} NodeType;

typedef struct {
  const char *name;
  int length;
} Identifier;

struct Node {
  NodeType type;
  Node *next;

  // Unary expression.
  UnaryOperator u_op;
  Node *u_value;

  // Binary expression.
  BinaryExpr *binary;

  // Let assign expr.
  LetAssign *let_assign;

  // Let set expr.
  LetSet *let_set;

  // Let get expr.
  LetGet *let_get;

  // Block expr.
  Node *body;

  // Number literal.
  double number;
};

struct BinaryExpr {
  Node *lhs;
  BinaryOperator b_op;
  Node *rhs;
};

struct LetAssign {
  Identifier ident;
  Node expr;
};

struct LetSet {
  Identifier ident;
  Node expr;
};

struct LetGet {
  Identifier ident;
};

Node newUnary(UnaryOperator op, Node node);

Node newBinary(Node lhs, BinaryOperator op, Node rhs);

Node newLetAssign(Identifier ident, Node expr);
Node newLetSet(Identifier ident, Node expr);
Node newLetGet(Identifier ident);

Node newNumber(double number);

Identifier newIdent(const char *start, int length);

#endif //UNTITLEDLANG_NODE_H

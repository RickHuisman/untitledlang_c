#include "node.h"

Identifier newIdent(const char *start, int length) {
  Identifier ident;
  ident.name = start;
  ident.length = length;

  return ident;
}

Node newUnary(UnaryOperator op, Node lhs) {
  Node node;
  node.type = NODE_UNARY;
  node.u_op = op;
  node.u_value = &lhs;

  return node;
}

Node newBinary(Node lhs, BinaryOperator op, Node rhs) {
  Node node;
  node.type = NODE_BINARY;

  BinaryExpr binary;
  binary.lhs = &lhs;
  binary.b_op = op;
  binary.rhs = &rhs;

  node.binary = &binary;

  return node;
}

Node newLetAssign(Identifier ident, Node expr) {
  LetAssign let;
  let.ident = ident;
  let.expr = expr;

  Node node;
  node.type = NODE_LET_ASSIGN;
  node.let_assign = &let;

  return node;
}

Node newLetSet(Identifier ident, Node expr) {
  LetSet let;
  let.ident = ident;
  let.expr = expr;

  Node node;
  node.type = NODE_LET_SET;
  node.let_set = &let;

  return node;
}

Node newLetGet(Identifier ident) {
  LetGet let;
  let.ident = ident;

  Node node;
  node.type = NODE_LET_GET;
  node.let_get = &let;

  return node;
}

Node newNumber(double value) {
  Node node;
  node.type = NODE_NUMBER;
  node.number = value;

  return node;
}

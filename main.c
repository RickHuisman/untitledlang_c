#include "parser.h"

int main() {
  char* source = "{ let x = 10; let y = 5; }";
  Node ast = parse(source);

  return 0;
}

#include <printf.h>
#include "parser.h"

int main() {
  char* source = "let x = 10; x = 10;";
  Node ast = parse(source);
  printf("test");

  return 0;
}

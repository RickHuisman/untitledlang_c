#include <stdbool.h>
#include <memory.h>
#include "tokenizer.h"

typedef struct Tokenizer {
    const char* start;
    const char* current;
} Tokenizer;

Tokenizer tokenizer;

static bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
         c == '_';
}

static bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

static bool isAtEnd() {
  return *tokenizer.current == '\0';
}

static char advance() {
  tokenizer.current++;
  return tokenizer.current[-1];
}

static char peekNext() {
  if (isAtEnd()) return '\0';
  return tokenizer.current[1];
}

static char peek() {
  return *tokenizer.current;
}

static void skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
      case ' ':
      case '\r':
      case '\t':
      case '\n':
        advance();
        break;
      default:
        return;
    }
  }
}

static bool match(char expected) {
  if (isAtEnd()) return false;
  if (*tokenizer.current != expected) return false;

  tokenizer.current++;
  return true;
}

Token errorToken(const char* message) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = tokenizer.start;
  token.length = (int)(tokenizer.current - tokenizer.start);

  return token;
}

Token makeToken(TokenType type) {
  Token token;
  token.type = type;
  token.start = tokenizer.start;
  token.length = (int)(tokenizer.current - tokenizer.start);

  return token;
}

static TokenType checkKeyword(int start, int length,
                              const char* rest, TokenType type) {
  if (tokenizer.current - tokenizer.start == start + length &&
      memcmp(tokenizer.start + start, rest, length) == 0) {
    return type;
  }

  return TOKEN_IDENTIFIER;
}

static TokenType identifierType() {
  switch (tokenizer.start[0]) {
    case 'l': return checkKeyword(1, 2, "et", TOKEN_LET);
  }

  return TOKEN_IDENTIFIER;
}

static Token identifier() {
  while (isAlpha(peek()) || isDigit(peek())) {
    advance();
  }

  return makeToken(identifierType());
}

static Token number() {
  while (isDigit(peek())) {
    advance();
  }

  // Look for a fractional part.
  if (peek() == '.' && isDigit(peekNext())) {
    // Consume the '.'.
    advance();

    while (isDigit(peek())) {
      advance();
    }
  }

  return makeToken(TOKEN_NUMBER);
}

Token scanToken() {
  skipWhitespace();

  tokenizer.start = tokenizer.current;

  if (isAtEnd()) return makeToken(TOKEN_EOF);

  char c = advance();

  if (isAlpha(c)) return identifier();
  if (isDigit(c)) return number();

  switch (c) {
    case '(': return makeToken(TOKEN_LEFT_PAREN);
    case ')': return makeToken(TOKEN_RIGHT_PAREN);
    case '{': return makeToken(TOKEN_LEFT_BRACE);
    case '}': return makeToken(TOKEN_RIGHT_BRACE);
    case ';': return makeToken(TOKEN_SEMICOLON);
    case ',': return makeToken(TOKEN_COMMA);
    case '.': return makeToken(TOKEN_DOT);
    case '-': return makeToken(TOKEN_MINUS);
    case '+': return makeToken(TOKEN_PLUS);
    case '/': return makeToken(TOKEN_SLASH);
    case '*': return makeToken(TOKEN_STAR);
    case '!':
      return makeToken(
              match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '=':
      return makeToken(
              match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
    case '<':
      return makeToken(
              match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
    case '>':
      return makeToken(
              match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
  }

  return errorToken("Unexpected character");
}

void initTokenizer(const char* source) {
  tokenizer.start = source;
  tokenizer.current = source;
}

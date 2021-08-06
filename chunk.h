#ifndef UNTITLEDLANG_CHUNK_H
#define UNTITLEDLANG_CHUNK_H

#include <stdint.h>
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
} Opcode;

typedef struct {
    int count;
    int capacity;
    uint8_t *code;
    int *lines;
    ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);

void freeChunk(Chunk *chunk);

void writeChunk(Chunk *chunk, uint8_t byte, int line);

int addConstant(Chunk *chunk, Value value);

#endif UNTITLEDLANG_CHUNK_H

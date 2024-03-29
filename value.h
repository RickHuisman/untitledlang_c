#ifndef UNTITLEDLANG_VALUE_H
#define UNTITLEDLANG_VALUE_H

typedef double Value;

typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif UNTITLEDLANG_VALUE_H
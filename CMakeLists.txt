cmake_minimum_required(VERSION 3.19)
project(untitledlang C)

set(CMAKE_C_STANDARD 99)

add_executable(untitledlang main.c chunk.c chunk.h value.c value.h memory.c memory.h tokenizer.c tokenizer.h parser.c parser.h node.c node.h)
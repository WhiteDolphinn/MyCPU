#ifndef TEXT_H
#define TEXT_H
#include <stdio.h>

struct string{
    char* position;
    int length;
    };

int num_of_symbols(const char* name_of_file);
int num_of_lines(char* text);
char* text_reader(FILE* file, const char* name_of_file);
struct string* begin_of_str_position(char* text, const int SIZE_SYMBOLS, int* SIZE_LINES);
void text_writer(FILE* file, struct string* strings, int n);

#endif

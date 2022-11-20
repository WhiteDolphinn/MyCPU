#ifndef TEXT_H
#define TEXT_H

struct string{
    char* position;
    int length;
    };

int num_of_symbols(const char* name_of_file);
char* text_reader(FILE* file, const char* name_of_file);
struct string* begin_of_str_position(char* text, const int SIZE_SYMBOLS, int* SIZE_LINES);

#endif

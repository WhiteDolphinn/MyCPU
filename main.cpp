#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "my_assembler.h"

const char *const SOURCE_FILE_NAME = "commands.asm";

int main()
{
    FILE* file = fopen(SOURCE_FILE_NAME, "rb");
    if (!file)  return 0;

    char* text = text_reader(file, SOURCE_FILE_NAME);
    int size_symbols = num_of_symbols(SOURCE_FILE_NAME);
    fclose(file);

    int num_of_lines = 0;
    struct string* strings = begin_of_str_position(text, size_symbols, &num_of_lines);

    FILE* file_asm = fopen("test.code", "w");
    if(!convertor(file_asm, strings, num_of_lines, size_symbols))
        printf("Error!!!");

    fclose(file_asm);
    free(strings);
    free(text);

    return 0;
}

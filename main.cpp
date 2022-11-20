#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "my_assembler.h"

int main()
{
    const char* name_of_file = "commands.asm";
    FILE* file = fopen(name_of_file, "rb");

    char* text = text_reader(file, name_of_file);

    int num_of_lines = 0;
    int num_of_symbols = num_of_symbols(name_of_file);

    struct string* strings = begin_of_str_positions(text, num_of_symbols, &num_of_lines);
    fclose(name_of_file);
    char* text_asm = convertor(strings, *num_of_lines, num_of_symbols);

    printf("%s", text);
    free(text);

    return 0;
}

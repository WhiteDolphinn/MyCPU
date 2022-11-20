#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "my_assembler.h"

int main()
{
    const char* name_of_file = "commands.asm";
    FILE* file = fopen(name_of_file, "rb");

    char* text = text_reader(file, name_of_file);
    fclose(file);

    int size_symbols = num_of_symbols(name_of_file);

    int num_of_lines = 0;

    struct string* strings = begin_of_str_position(text, size_symbols, &num_of_lines);
    printf("%d", num_of_lines);
    char* text_asm = convertor(strings, num_of_lines, size_symbols);
        printf("%d", __LINE__);

    FILE* file_asm = fopen("test.code", "w");
  //  text_writer(file_asm, text_asm, num_of_lines);
    fprintf(file_asm, "%s", text_asm);
    fclose(file_asm);

    printf("%s\n%s\n", text, text_asm);
    free(text);
    free(text_asm);

    return 0;
}

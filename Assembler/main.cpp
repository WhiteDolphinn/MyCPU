#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "my_assembler.h"

//const char *const SOURCE_FILE_NAME = "Assembler/test.asm";
void help();

int main(int argc, const char* argv[])
{
    const char* SOURCE_FILE_NAME = argv[1];

    if(argc != 2)
    {
        help();
        return 0;
    }

    FILE* file = fopen(SOURCE_FILE_NAME, "rb");
    if (!file)
    {
        printf("I can't open <%s>\n", SOURCE_FILE_NAME);
        return 0;
    }

    char* text = text_reader(file, SOURCE_FILE_NAME);
    int size_symbols = num_of_symbols(SOURCE_FILE_NAME);
    fclose(file);

    int num_of_lines = 0;
    struct string* strings = begin_of_str_position(text, size_symbols, &num_of_lines);

    FILE* file_asm = fopen("Assembler/test.code", "w");
    int uncorrect_line = 0;
    if(!convertor(file_asm, strings, num_of_lines, &uncorrect_line))
        fprintf(file_asm, "\n\nError in %d line!!!\n", uncorrect_line);

    fclose(file_asm);
    free(strings);
    free(text);

    return 0;
}

void help()
{
    printf("You should write name of file after the ./a.out\n");
    printf("./a.out \"name_of_source_file\"\n");
}

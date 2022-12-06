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

    FILE* file_asm_txt = fopen("Assembler/test.code", "w");
    FILE* file_asm_bin = fopen("Assembler/test.bin", "wb");

    int* link_positions = (int*)calloc(NUM_OF_LINKS, sizeof(int));
    //link_positions = check_links(link_positions, strings, num_of_lines);

    int uncorrect_line = 0;
    if(link_positions != nullptr)
    {
    if(!convertor(file_asm_txt, file_asm_bin,  strings, num_of_lines, &uncorrect_line, link_positions, 1))
        printf("\n\nError in %d line!!!\n", uncorrect_line);
    }

    fclose(file_asm_txt);
    fclose(file_asm_bin);
    file_asm_txt = fopen("Assembler/test.code", "w");
    file_asm_bin = fopen("Assembler/test.bin", "wb");

    if(!convertor(file_asm_txt, file_asm_bin,  strings, num_of_lines, &uncorrect_line, link_positions, 2))
        printf("\n\nError in %d line!!!\n", uncorrect_line);

    fclose(file_asm_txt);
    fclose(file_asm_bin);
    free(link_positions);
    free(strings);
    free(text);

    return 0;
}

void help()
{
    printf("You should write name of file after the ./a.out\n");
    printf("./a.out \"name_of_source_file\"\n");
    printf("Assembler/test.asm (default)\n");
}

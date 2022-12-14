#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "my_assembler.h"

//const char *const SOURCE_FILE_NAME = "Assembler/test.asm";
void help();

int main(int argc, const char* argv[])
{
    const char* SOURCE_FILE_NAME = argv[1];
    const char* BIN_FILE = argv[2];
    const char* TXT_FILE = "Assembler/test.code";

    if(argc != 3)
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

    FILE* file_asm_txt = fopen(TXT_FILE, "w");
    FILE* file_asm_bin = fopen(BIN_FILE, "wb");

    if(file_asm_txt == nullptr || file_asm_bin == nullptr)
    {
        if(file_asm_txt == nullptr)
            printf("I can't open <%s> file\n", TXT_FILE);
        else
            printf("I can't open <%s> file\n", BIN_FILE);

        free(strings);
        free(text);
        fclose(file_asm_txt);
        fclose(file_asm_bin);
        return 0;
    }

    int* link_positions = (int*)calloc(NUM_OF_LINKS, sizeof(int));

    /*for(int i = 0; i < NUM_OF_LINKS; i++)
        link_positions[i] = -1;*/

    int uncorrect_line = 0;
    if(link_positions != nullptr)
    {
    if(!convertor(file_asm_txt, file_asm_bin,  strings, num_of_lines, &uncorrect_line, link_positions, 1))
        printf("\n\nError in %d line!!!\n", uncorrect_line);
    }

    fclose(file_asm_txt);
    fclose(file_asm_bin);
    file_asm_txt = fopen(TXT_FILE, "w");
    file_asm_bin = fopen(BIN_FILE, "wb");

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
    printf("a.out [NAME_OF_SOURCE_FILE] [NAME_OF_BIN_FILE]\n");
    printf("a.out Assembler/test.asm Assembler/test.bin  (default)\n");
}

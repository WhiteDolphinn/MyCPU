#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "my_assembler.h"

static void help();
static struct string* get_strings(const char* SOURCE_FILE_NAME, char** text, int* num_of_lines, int* error);

enum err{
    OK = 0,
    ERR_OP_SOURCE_FILE = 1,
    ERR_LINK_POSITIONS = 2,
    ERR_OP_TXT_FILE = 3,
    ERR_OP_BIN_FILE = 4,

};

int main(int argc, const char* argv[])
{
    int error = 0;

    if(argc != 3)
    {
        help();
        return 0;
    }

    const char* SOURCE_FILE_NAME = argv[1];
    const char* BIN_FILE = argv[2];
    const char* TXT_FILE = "Assembler/test.code";

    char* text = nullptr;
    int num_of_lines = 0;
    struct string* strings = get_strings(SOURCE_FILE_NAME, &text, &num_of_lines, &error);
    if(strings == nullptr)
    {
        free(strings);
        free(text);
        return error;
    }

    FILE* file_asm_txt = fopen(TXT_FILE, "w");
    FILE* file_asm_bin = fopen(BIN_FILE, "wb");
     int* link_positions = (int*)calloc(NUM_OF_LINKS, sizeof(int));

    if(file_asm_txt == nullptr || file_asm_bin == nullptr)
    {
        if(!file_asm_txt)
        {
            error = ERR_OP_TXT_FILE;
            printf("I can't open <%s> file\n", TXT_FILE);
        }
        if(!file_asm_bin)
        {
            error = ERR_OP_BIN_FILE;
            printf("I can't open <%s> file\n", BIN_FILE);
        }

        goto exit;
    }

    if(link_positions == nullptr)
    {
        printf("nijuhai bebroo\n");
        error = ERR_LINK_POSITIONS;

        goto exit;
    }

    if(link_positions != nullptr)
    {
        int uncorrect_line = 0;
        if(!convertor(file_asm_txt, file_asm_bin,  strings, num_of_lines, &uncorrect_line, link_positions, 1))
            printf("\n\nError in %d line!!!\n", uncorrect_line);
    }

    fclose(file_asm_txt);
    fclose(file_asm_bin);
    file_asm_txt = fopen(TXT_FILE, "w");
    file_asm_bin = fopen(BIN_FILE, "wb");

    if(link_positions != nullptr)
    {
        int uncorrect_line = 0;
        if(!convertor(file_asm_txt, file_asm_bin,  strings, num_of_lines, &uncorrect_line, link_positions, 2))
            printf("\n\nError in %d line!!!\n", uncorrect_line);
    }

    exit:
    fclose(file_asm_txt);
    fclose(file_asm_bin);
    free(link_positions);
    free(strings);
    free(text);

    return error;
}

static void help()
{
    printf("a.out [NAME_OF_SOURCE_FILE] [NAME_OF_BIN_FILE]\n");
    printf("a.out Assembler/test.asm Assembler/test.bin  (default)\n");
}

static struct string* get_strings(const char* SOURCE_FILE_NAME, char** text, int* num_of_lines, int* error)
{
    FILE* source_file = fopen(SOURCE_FILE_NAME, "rb");
    if (!source_file)
    {
        printf("I can't open <%s>\n", SOURCE_FILE_NAME);
        *error = ERR_OP_SOURCE_FILE;
        return nullptr;
    }

    *text       = text_reader    (source_file, SOURCE_FILE_NAME);
    int size_symbols = num_of_symbols (SOURCE_FILE_NAME);

    fclose(source_file);

    struct string* strings = begin_of_str_position(*text, size_symbols, num_of_lines);
    return strings;
}


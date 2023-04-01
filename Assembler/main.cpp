#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "text.h"
#include "my_assembler.h"

static void help();
static struct string* get_strings(const char* SOURCE_FILE_NAME, char** text, int* num_of_lines, int* error);
static char* get_filename(const char* source_file, const char* addition);
static bool check_openings_of_files(FILE* file1, FILE* file2, char* file1_name, char* file2_name, int* error);

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

    if(argc != 2)
    {
        help();
        return 0;
    }

    const char* SOURCE_FILE_NAME = argv[1];
    char* BIN_FILE = get_filename(SOURCE_FILE_NAME, "bin");
    char* TXT_FILE = get_filename(SOURCE_FILE_NAME, "code");

    char* text = nullptr;
    int num_of_lines = 0;
    struct string* strings = get_strings(SOURCE_FILE_NAME, &text, &num_of_lines, &error);
    if(strings == nullptr)
    {
        free(strings);
        free(text);
        free(BIN_FILE);
        free(TXT_FILE);
        return error;
    }

    FILE* file_asm_txt = fopen(TXT_FILE, "w");
    FILE* file_asm_bin = fopen(BIN_FILE, "wb");
    int* link_positions = (int*)calloc(NUM_OF_LINKS, sizeof(int));

    if(!check_openings_of_files(file_asm_txt, file_asm_bin, TXT_FILE, BIN_FILE, &error))
        goto exit;

    if(link_positions == nullptr)
    {
        printf("nijuhai bebroo\n");
        error = ERR_LINK_POSITIONS;

        goto exit;
    }

    {
    int uncorrect_line = 0;
    if(!convertor(file_asm_txt, file_asm_bin,  strings, num_of_lines, &uncorrect_line, link_positions, 1))
        printf("\n\nError in %d line!!!\n", uncorrect_line);

    fclose(file_asm_txt);
    fclose(file_asm_bin);
    file_asm_txt = fopen(TXT_FILE, "w");
    file_asm_bin = fopen(BIN_FILE, "wb");

    if(!check_openings_of_files(file_asm_txt, file_asm_bin, TXT_FILE, BIN_FILE, &error))
        goto exit;

    uncorrect_line = 0;
    if(!convertor(file_asm_txt, file_asm_bin,  strings, num_of_lines, &uncorrect_line, link_positions, 2))
        printf("\n\nError in %d line!!!\n", uncorrect_line);

    }
    exit:
    free(BIN_FILE);
    free(TXT_FILE);
    fclose(file_asm_txt);
    fclose(file_asm_bin);
    free(link_positions);
    free(strings);
    free(text);

    return error;
}

static void help()
{
    printf("<name_of_source_file>\t\tName of the assembler code file\n");
}

static struct string* get_strings(const char* source_file_name, char** text, int* num_of_lines, int* error)
{
    FILE* source_file = fopen(source_file_name, "rb");
    if (!source_file)
    {
        printf("I can't open <%s>\n", source_file_name);
        *error = ERR_OP_SOURCE_FILE;
        return nullptr;
    }

    *text = text_reader(source_file, source_file_name);
    int size_symbols = num_of_symbols(source_file_name);

    fclose(source_file);

    struct string* strings = begin_of_str_position(*text, size_symbols, num_of_lines);
    return strings;
}

static char* get_filename(const char* source_filename, const char* addition)
{
    char* new_filename = (char*)calloc(strlen(source_filename) + strlen(addition), sizeof(char));
    const char* point_position = source_filename + strlen(source_filename);
    for( ;point_position != source_filename; point_position--)
    {
        if(*point_position == '.')
            break;
    }
    if(point_position == source_filename) // файл без расширения
        point_position = source_filename + strlen(source_filename);

    strncpy(new_filename, source_filename, (size_t)(point_position - source_filename + 1));
    *(new_filename + (point_position - source_filename) + 1) = '\0';
    strcat(new_filename, addition);
    return new_filename;
}

static bool check_openings_of_files(FILE* file1, FILE* file2, char* file1_name, char* file2_name, int* error)
{
    if(file1 == nullptr || file2 == nullptr)
    {
        if(!file1)
        {
            *error = ERR_OP_TXT_FILE;
            printf("I can't open <%s> file\n", file1_name);
        }
        if(!file2)
        {
            *error = ERR_OP_BIN_FILE;
            printf("I can't open <%s> file\n", file2_name);
        }
        return false;
    }
    return true;
}

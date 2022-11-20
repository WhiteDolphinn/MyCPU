#include <string.h>
#include <stdlib.h>
#include "text.h
#include "my_assembler.h"

char* convertor(char* text, struct string* strings, int num_of_lines, int num_of_symbols)
{
    char* ptr = text;
    char* text_asm = calloc(num_of_symbols(num_of_symbols), sizeof(char));


    while(is_any_command(ptr))
    {

        strncpy(text_asm, ptr, ptr - );
        change_str("1", "push", strlen("1"), strlen("push"));
    }

    return text_asm;
}

int is_any_command()
{

}

void change_str(const char* code, const char* name, int code_len, int name_len)
{

}

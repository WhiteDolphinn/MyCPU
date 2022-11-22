#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "my_assembler.h"

const char *const SOURCE_FILE_NAME = "commands.asm";

int main()
{
    FILE* file = fopen(SOURCE_FILE_NAME, "rb");

    if (!file) return 0;

    char* text = text_reader(file, SOURCE_FILE_NAME);

    int size_symbols = num_of_symbols(SOURCE_FILE_NAME);
    fclose(file);

    int num_of_lines = 0;

    struct string* strings = begin_of_str_position(text, size_symbols, &num_of_lines);
   // printf("%d", size_symbols);

 //int/*bool*/ convertor(strings, ..., fileToWrite);



   // char* text_asm = old_convertor(strings, num_of_lines, size_symbols);
        //printf("%d", __LINE__);
    FILE* file_asm = fopen("test.code", "w");
    if(!convertor(file_asm, strings, num_of_lines, size_symbols))
        printf("Error!!!");
    //text_writer(file_asm, text_asm, num_of_lines);
  //  fprintf(file_asm, "%s", text_asm);
    fclose(file_asm);

   // printf("%s\n%s\n", text, text_asm);
    free(strings);
    free(text);
   // free(text_asm);

    return 0;
}

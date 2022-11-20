#include <stdio.h>
#include <stdlib.h>
#include "text.h"

int main()
{
    const char* name_of_file = "commands.asm";
    FILE* file = fopen(name_of_file, "rb");

    char* text = text_reader(file, name_of_file);
    printf("%s", text);
    free(text);

    return 0;
}

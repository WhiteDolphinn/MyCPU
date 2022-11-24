#include <stdlib.h>
#include "soft_cpu.h"
#include "text.h"

int* read_source_file(const char* name_of_source_file)
{
    FILE* source_file = fopen(name_of_source_file, "rb");

    int* commands = (int*)calloc(num_of_symbols(name_of_source_file), sizeof(int));
    fread(commands, sizeof(int), num_of_symbols(name_of_source_file), source_file);

    fclose(source_file);
    return commands;
}

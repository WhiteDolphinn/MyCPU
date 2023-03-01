#include <stdio.h>
#include <stdlib.h>
#include "my_assembler.h"
#include "text.h"
#include "soft_cpu.h"
#include "log.h"

static void help();

int main(int argc, const char* argv[])
{
    if(argc != 2)
    {
        help();
        return 0;
    }

    const char* name_of_source_file = argv[1];
    int* commands = read_source_file(name_of_source_file);

    if(commands == nullptr)
        return 0;

    struct cpu cpu;
    start_cpu(&cpu, commands);

    execute_cmds(&cpu);

    stop_cpu(&cpu);
    return 0;
}

static void help()
{
    printf("<name_of_source_file>\t\tName of the .bin file with bin-code\n");
}

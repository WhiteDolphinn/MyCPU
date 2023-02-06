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

    struct cpu cpu;
    start_cpu(&cpu, commands);

    execute_cmds(&cpu);

    stop_cpu(&cpu);
    //close_log_file();
    return 0;
}

static void help()
{
    //printf("You should write name of  .bin file after the ./a.out\n");
    //printf("./a.out <name_of_source_file>\n");
    //printf("Assembler/test.bin (default)\n");
    printf("<name_of_source_file>\t\tName of the .bin file with bin-code\n");
}

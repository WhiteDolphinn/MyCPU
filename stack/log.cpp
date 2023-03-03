#include "log.h"
#include "stack.h"
#include <time.h>
#include <stdlib.h>
#include <assert.h>

FILE* get_log_file()
{
    time_t timer = time(NULL);
    struct tm* time = localtime(&timer);

    char filename[100] = "";

    sprintf(filename, ".log/%d_%d_%d_%d_%d_log.txt", time->tm_hour, time->tm_min, time->tm_mday,
            time->tm_mon+1, time->tm_year+1900);

    static FILE* log_file = nullptr;

    if(log_file == nullptr)
    {
        if(PRINT_IN_CONSOLE == 0)

        {
            log_file = fopen(filename, "w");
            atexit(close_log_file);
        }
        else
            log_file = stdout;
    }

    return log_file;
}

void close_log_file()
{
  //  printf("1\n");

   FILE*f=(get_log_file());

  // fprintf(f, "hhhhh11\n");
   //printf("%p\n",f);
   fclose(f);
    //printf("2\n");
}

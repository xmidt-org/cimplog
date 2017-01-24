#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cimplog.h"

void __cimplog(const char *module, int level, const char *msg, ...)
{
    char buf[MAX_BUF_SIZE], *bp;
    int nbytes, module_length = strlen(module);
    va_list arg_ptr;
    struct timespec ts;

    clock_gettime(CLOCK_REALTIME, &ts);
    nbytes = sprintf(buf, "[%09ld] ", ts.tv_sec); 
    if( nbytes < 0 )
    {   
        printf("Error occurred in sprintf\n");
        return;
    }
    bp = buf+nbytes;
    nbytes = snprintf(bp, module_length+4, "[%s] ", module);
    if( nbytes < 0 )
    {   
        printf("Error occurred in snprintf, module\n");
        return;
    }
    bp += nbytes;

    if( level == LEVEL_ERROR )
    {
        nbytes = snprintf(bp, 8, "Error: ");
    }   
    else if( level == LEVEL_INFO )
    {   
        nbytes = snprintf(bp, 7, "Info: ");
    }   
    else if( level == LEVEL_DEBUG )
    {   
        nbytes = snprintf(bp, 8, "Debug: ");
    }
    if( nbytes < 0 )
    {   
        printf("Error occurred in snprintf, level\n");
        return;
    }
    bp += nbytes;

    va_start(arg_ptr, msg);
    nbytes = vsnprintf(bp, (MAX_BUF_SIZE - (bp - buf)), msg, arg_ptr);
    va_end(arg_ptr);
    if( nbytes < 0 )
    {
        printf("Error occurred in vsnprintf\n");
        return;
    }

    printf("%s", buf);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rdk_debug.h>

#include "cimplog.h"

#define MAX_BUF_SIZE 1024

const char *__attribute__((weak)) rdk_logger_module_fetch(void);

void __cimplog(const char *module, int level, const char *msg, ...)
{
    static const rdk_LogLevel _level[] = { RDK_LOG_ERROR, RDK_LOG_INFO, RDK_LOG_DEBUG };
    static const char *rdk_logger_module = NULL;
    va_list arg_ptr;
    char buf[MAX_BUF_SIZE];
    int nbytes;

    if( NULL == rdk_logger_module )
    {
        rdk_logger_init("/etc/debug.ini");
        rdk_logger_module = rdk_logger_module_fetch();
	if( NULL == rdk_logger_module )
        {
            fprintf(stderr, "\nERROR: Unable to initialize RDK logging!!!\n");
            exit(0);
        }
    }

    va_start(arg_ptr, msg);
    nbytes = vsnprintf(buf, MAX_BUF_SIZE, msg, arg_ptr);
    va_end(arg_ptr);

    if( nbytes >=  MAX_BUF_SIZE )	
    {
    	buf[ MAX_BUF_SIZE - 1 ] = '\0';
    }
    else
    {
    	buf[nbytes] = '\0';
    }
    

    RDK_LOG(_level[0x2 & level], rdk_logger_module, "%s: %s", module, buf);
}

const char *rdk_logger_module_fetch(void)
{
    return NULL;
}


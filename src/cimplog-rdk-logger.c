#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <rdk_debug.h>

#include "cimplog.h"

#define MAX_BUF_SIZE 1024
#define DEFAULT_MODULE "NO MODULE"

static bool __rdk_logger_init = false;

char *__attribute__((weak)) rdk_logger_module_fetch(void);

void __cimplog(const char *module, int level, const char *msg, ...)
{
    static const rdk_LogLevel _level[] = { RDK_LOG_ERROR, RDK_LOG_INFO, RDK_LOG_DEBUG };
    va_list arg_ptr;
    char buf[MAX_BUF_SIZE];
    char *rdk_logger_module = NULL;
    int nbytes;

    if( false == __rdk_logger_init )
    {
        rdk_logger_init("/etc/debug.ini");
        rdk_logger_module = rdk_logger_module_fetch();
        if( !rdk_logger_module )
        {
            printf("\nERROR: Unable to initialize RDK logging!!!\n");
            return;
        }
        __rdk_logger_init = true;
    }

    va_start(arg_ptr, msg);
    nbytes = vsnprintf(buf, MAX_BUF_SIZE, msg, arg_ptr);
    va_end(arg_ptr);
    buf[nbytes] = '\0';

    RDK_LOG(_level[0x2 & level], rdk_logger_module, "%s: %s", module, buf);
}

char *rdk_logger_module_fetch(void)
{
    return (DEFAULT_MODULE);
}


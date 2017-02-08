#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <rdk_debug.h>

#include "cimplog.h"

#define MAX_BUF_SIZE 1024

static bool __rdk_logger_init = false;
static char __rdk_logger_module[MAX_BUF_SIZE];

char *__attribute__((weak)) rdk_logger_module_fetch(void);

void __cimplog(const char *module, int level, const char *msg, ...)
{
    static const rdk_LogLevel _level[] = { RDK_LOG_ERROR, RDK_LOG_INFO, RDK_LOG_DEBUG };
    va_list arg_ptr;
    char buf[MAX_BUF_SIZE];
    char *tmp = NULL;
    int nbytes;

    if( false == __rdk_logger_init )
    {
        rdk_logger_init("/etc/debug.ini");
        tmp = rdk_logger_module_fetch();
        if( tmp )
        {
            int nlen_str = strlen(tmp);
            int nlength = (MAX_BUF_SIZE < nlen_str) ? MAX_BUF_SIZE : nlen_str;
            strncpy(__rdk_logger_module, tmp, nlength);
            __rdk_logger_module[nlength] = '\0';
        }
        __rdk_logger_init = true;
    }

    va_start(arg_ptr, msg);
    nbytes = vsnprintf(buf, MAX_BUF_SIZE, msg, arg_ptr);
    va_end(arg_ptr);
    buf[nbytes] = '\0';

    RDK_LOG(_level[0x2 & level], __rdk_logger_module, "%s: %s", module, buf);
}


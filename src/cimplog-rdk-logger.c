#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rdk_debug.h>

#include "cimplog.h"

#define MAX_BUF_SIZE 1024

void __cimplog(const char *module, int level, const char *msg, ...)
{
    static const rdk_LogLevel _level[] = { RDK_LOG_ERROR, RDK_LOG_INFO, RDK_LOG_DEBUG };
    va_list arg_ptr;
    char buf[MAX_BUF_SIZE];
    int nbytes;

    va_start(arg_ptr, msg);
    nbytes = vsnprintf(buf, MAX_BUF_SIZE, msg, arg_ptr);
    va_end(arg_ptr);
    buf[nbytes] = '\0';

    RDK_LOG(_level[0x2 & level], module, "%s", buf);
}


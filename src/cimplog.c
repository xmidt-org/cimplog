#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cimplog.h"

#define MAX_BUF_SIZE 1024

void cimplog_init(void)
{
   /* Empty stub. */
}

void __cimplog(const char *module, int level, const char *msg, ...)
{
    static const char *_level[] = { "Error", "Info", "Debug", "Unknown" };
    va_list arg_ptr;
    char buf[MAX_BUF_SIZE];
    int nbytes;
    struct timespec ts;

    va_start(arg_ptr, msg);
    nbytes = vsnprintf(buf, MAX_BUF_SIZE, msg, arg_ptr);
    va_end(arg_ptr);
    buf[nbytes]='\0';

    clock_gettime(CLOCK_REALTIME, &ts);

    printf("[%09ld][%s][%s]: %s", ts.tv_sec, module, _level[0x3 & level], buf);
}


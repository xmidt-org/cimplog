/**
 * Copyright 2016 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cimplog.h"

#define MAX_BUF_SIZE 1024

#if defined(LEVEL_DEFAULT)
int cimplog_debug_level = LEVEL_DEFAULT;
#else
int cimplog_debug_level = LEVEL_INFO;
#endif

void __cimplog(const char *module, int level, const char *msg, ...)
{
    static const char *_level[] = { "Error", "Info", "Debug", "Unknown" };
    va_list arg_ptr;
    char buf[MAX_BUF_SIZE];
    int nbytes;
    struct timespec ts;

    printf("cimplog -- cimplog_debug_level = %d\n", cimplog_debug_level);
    if (level <= cimplog_debug_level)
    {
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
    
        clock_gettime(CLOCK_REALTIME, &ts);

        printf("[%09ld][%s][%s]: %s", ts.tv_sec, module, _level[0x3 & level], buf);
    }
}


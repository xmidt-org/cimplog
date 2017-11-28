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

static cimplog_handler_t _log_handler = NULL;

void cimplog_stdout(int level, const char* moduel, const char* format, va_list args);
void cimplog_rdk(int level, const char* module, const char* format, va_list args);

void __cimplog(const char *module, int level, const char* format, ...)
{
  va_list args;
  va_start(args, format);

  if (_log_handler)
  {
    _log_handler(level, module, format, args);
  }
  else
  {
    #ifdef RDK_LOGGER
    cimplog_rdk(level, module, format, args);
    #else
    cimplog_stdout(level, module, format, args);
    #endif
  }

  va_end(args);
}

void
cimplog_stdout(int level, const char* module, const char* format, va_list args)
{
    static const char *_level[] = { "Error", "Info", "Debug", "Unknown" };

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    printf("[%09ld][%s][%s]: ", ts.tv_sec, module, _level[0x3 & level]);
    vprintf(format, args);
}

void
cimplog_sethandler(cimplog_handler_t handler)
{
  _log_handler = handler;
}

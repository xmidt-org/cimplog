/**
 * Copyright 2017 Comcast Cable Communications Management, LLC
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
#ifndef __CIMPLOG_H__
#define __CIMPLOG_H__

#include <stdarg.h>

#define LEVEL_ERROR    0
#define LEVEL_INFO     1
#define LEVEL_DEBUG    2

#define cimplog_error(module, ...)    __cimplog(module, LEVEL_ERROR, __VA_ARGS__)
#define cimplog_info(module, ...)     __cimplog(module, LEVEL_INFO, __VA_ARGS__)
#define cimplog_debug(module, ...)    __cimplog(module, LEVEL_DEBUG, __VA_ARGS__)

/**
 * @brief application provided log handler instead of default stdout
 *
 * @param module Library or Module indication
 * @param level  ERROR, INFO, or DEBUG
 * @param msg    The formatted log message
 */
typedef void (*cimplog_handler_t)(int level, const char* module, const char* format, va_list args);

/**
 * @briege Sets an application log handler instead of using default stdout
 *
 * @param handler The application logging callback
 */
void cimplog_sethandler(cimplog_handler_t handler);

/**
* @brief handle log message based on log level
* 
* @param module string identifying library/module
* @param level of log is info,debug,error
* @param msg message
*/
void __cimplog(const char *module, int level, const char *msg, ...)
  __attribute__ ((format (printf, 3, 4)));


#endif

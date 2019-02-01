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
#include <sys/sysinfo.h>
#include <time.h>
#include <string.h>
#include "cimplog.h"

#define MAX_BUF_SIZE 1024

#ifdef XB3_ARM
#define ONBOARDING_FILE         "/rdklogs/logs/OnBoardingLog_Arm.txt.0"
#elif XB3_ATOM
#define ONBOARDING_FILE         "/rdklogs/logs/OnBoardingLog_Atom.txt.0"
#else
#define ONBOARDING_FILE         "/rdklogs/logs/OnBoardingLog.txt.0"
#endif

void __cimplog_generic(const char *module, const char *msg, ...)
{
    va_list arg_ptr;
    char buf[MAX_BUF_SIZE];
    int nbytes;
    struct sysinfo l_sSysInfo;
    struct tm * l_sTimeInfo;
    char l_cLocalTime[32] = {0};
    time_t l_sNowTime;
    FILE *l_fOnBoardingLogFile = NULL;

    sysinfo(&l_sSysInfo);
    time(&l_sNowTime);
    l_sTimeInfo = localtime(&l_sNowTime);

    strftime(l_cLocalTime,32, "%y%m%d-%X",l_sTimeInfo);
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

    l_fOnBoardingLogFile = fopen(ONBOARDING_FILE, "a+");
    if (NULL != l_fOnBoardingLogFile)
    {
        if(module != NULL)
        {
            fprintf(l_fOnBoardingLogFile, "%s [%s] %s", l_cLocalTime, module, buf);
        }
        else
        {
            fprintf(l_fOnBoardingLogFile, "%s %s", l_cLocalTime, buf);
        }
        fclose(l_fOnBoardingLogFile);
    }
    else //fopen of on boarding file failed atleast write on the console
    {
        if(module != NULL)
        {
            printf("%s [%s] %s", l_cLocalTime, module, buf);
        }
        else
        {
            printf("%s %s", l_cLocalTime, buf);
        }
    }
}

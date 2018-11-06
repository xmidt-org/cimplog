/**
 *  Copyright 2017 Comcast Cable Communications Management, LLC
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <time.h>
#include <rdk_debug.h>

#include "../src/cimplog.h"

#define MAX_BUF_SIZE 1024

int rdk_logger_init(char* str)
{
    printf("%s\n", str);
    return 0;
}

void log_rdk(rdk_LogLevel level, const char *module,
        const char *format, ...)
{
    static const char *_level[] = { "Error", "Info", "Debug" }; 
    va_list arg_ptr;
    char buf[MAX_BUF_SIZE];
    int nbytes;
    struct timespec ts;

    va_start(arg_ptr, format);
    nbytes = vsnprintf(buf, MAX_BUF_SIZE, format, arg_ptr);
    va_end(arg_ptr);
    buf[nbytes]='\0';

    clock_gettime(CLOCK_REALTIME, &ts);

    printf("[%09ld][%s][%s]: %s", ts.tv_sec, module, _level[0x3 & level], buf);
}

void test_cimplog_err()
{
    char mod2[] = "Module2", mod3[] = "Module3";

    cimplog_error("Module1", "Sample error\n");
    cimplog_info(mod2, "Sample info\n");
    cimplog_debug(mod3, "Sample debug\n");

    __cimplog(mod2, 3, "Sample unknown level message");
}

void add_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "cimplog tests", NULL, NULL );
    CU_add_test( *suite, "Test cimplog logging error\n", test_cimplog_err );
}

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
int main( void )
{
    unsigned rv = 1;
    CU_pSuite suite = NULL;

    if( CUE_SUCCESS == CU_initialize_registry() ) {
        add_suites( &suite );

        if( NULL != suite ) {
            CU_basic_set_mode( CU_BRM_VERBOSE );
            CU_basic_run_tests();
            printf( "\n" );
            CU_basic_show_failures( CU_get_failure_list() );
            printf( "\n\n" );
            rv = CU_get_number_of_tests_failed();
        }

        CU_cleanup_registry();
    }

    if( 0 != rv ) {
        return 1;
    }

    return 0;
}


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

#include "../src/cimplog.h"

static int callback_count = 0;

static void
my_log_callback(int level, const char* module, const char* format, va_list args)
{
  int n;
  char buff[64];

  (void) level;
  (void) module;

  CU_ASSERT(level == LEVEL_INFO);
  CU_ASSERT(strcmp(module, "module") == 0);
  CU_ASSERT(strcmp(format, "%d") == 0);

  vsnprintf(buff, sizeof(buff), format, args);
  n = (int) strtol(buff, NULL, 10);
  callback_count += n;
}

void test_simple()
{
    char mod2[] = "Module2", mod3[] = "Module3";

    cimplog_error("Module1", "Sample error\n");
    cimplog_info(mod2, "Sample info\n");
    cimplog_debug(mod3, "Sample debug\n");
}

void test_log_callback()
{
  cimplog_sethandler(my_log_callback);
  cimplog_info("module", "%d", 1);
  cimplog_info("module", "%d", 2);
  cimplog_info("module", "%d", 3);
  cimplog_info("module", "%d", 4);
  cimplog_info("module", "%d", 5);
  CU_ASSERT(callback_count == 15);
}

void add_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "cimplog tests", NULL, NULL );
    CU_add_test( *suite, "Test simple logging", test_simple );
    CU_add_test( *suite, "Test log callback", test_log_callback);
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


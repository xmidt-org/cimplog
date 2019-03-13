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

void test_cimplog()
{
    char mod2[] = "Module2", mod3[] = "Module3";

    cimplog_error("Module1", "Sample error\n");
    cimplog_info(mod2, "Sample info\n");
    cimplog_debug(mod3, "Sample debug\n");
}

void test_onBoarding()
{
    char mod2[] = "Module2";
    char *msg = "arguments";
    onboarding_log("Module1", "Sample OnBoarding Log\n");
    onboarding_log(mod2, "Sample OnBoarding Log with %s\n",msg);
    onboarding_log(NULL, "Sample debug\n");
}
void add_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "cimplog tests", NULL, NULL );
    CU_add_test( *suite, "Test cimplog logging\n", test_cimplog );
    CU_add_test( *suite, "Test onboard logging\n", test_onBoarding );
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


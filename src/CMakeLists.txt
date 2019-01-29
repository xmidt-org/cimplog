#   Copyright 2016 Comcast Cable Communications Management, LLC
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

set(PROJ_CIMPL cimplog)

file(GLOB HEADERS cimplog.h cimplog.h)
if (RDK_LOGGER)
set(SOURCES cimplog-rdk-logger.c cimplog-onboarding.c)
else (RDK_LOGGER)
set(SOURCES cimplog.c cimplog-onboarding.c)
endif (RDK_LOGGER)

add_library(${PROJ_CIMPL} STATIC ${HEADERS} ${SOURCES})
add_library(${PROJ_CIMPL}.shared SHARED ${HEADERS} ${SOURCES})
set_target_properties(${PROJ_CIMPL}.shared PROPERTIES 
        OUTPUT_NAME ${PROJ_CIMPL}
        SOVERSION "1.0.0")

# ----------------------------------------------------------------------------
# Note: This is a partial solution and only covers the case required for the
# Yocto build (ie dynamic lib + rdk logger). Other cases may need fixing too.
# ----------------------------------------------------------------------------
if (RDK_LOGGER)
target_link_libraries(${PROJ_CIMPL}.shared rdkloggers log4c)
endif (RDK_LOGGER)
# ----------------------------------------------------------------------------

install (TARGETS ${PROJ_CIMPL} 
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib)
install (TARGETS ${PROJ_CIMPL} DESTINATION lib${LIB_SUFFIX})
install (TARGETS ${PROJ_CIMPL}.shared DESTINATION lib${LIB_SUFFIX})
install (FILES cimplog.h DESTINATION include/${PROJ_CIMPL})

#-------------------------------------------------------------------------------
# onboarding_log cli
#-------------------------------------------------------------------------------
set(BIN_SOURCES cimplog-onboarding.c main.c)
add_executable(onboarding_log ${BIN_SOURCES} ${HEADERS})
install (TARGETS onboarding_log DESTINATION bin)

/*
 * ============================================================================
 * COMCAST C O N F I D E N T I A L AND PROPRIETARY
 * ============================================================================
 * This file (and its contents) are the intellectual property of Comcast.  It may
 * not be used, copied, distributed or otherwise  disclosed in whole or in part
 * without the express written permission of Comcast.
 * ============================================================================
 * Copyright (c) 2013 Comcast. All rights reserved.
 * ============================================================================
 */

/**
 * @file rdk_debug.h
 * The header file provides RDK debug APIs.
 */

/**
 * @defgroup RDKLOGGER RDK Logger
 * RDK Logger provides common logging capability for all RDK components.
 * It is a common logging library which is based on MPEOS logging & uses log4c for
 * formatting and supports multiple log levels.
 *
 * @par RDK Logger Capabilities
 *
 * - Abstracts logging client from underlying logging utility.
 * - Dynamically enables/disables logging level at run time.
 * - Provides logging format that complies with the existing OCAP format (e.g. <timestamp> [mod=*, level=*]).
 * - Controls log level independently for each component/module.
 * - Enables logging globally via single configuration value.
 * - Controls initial log level for each component/module from configuration file (debug.ini) at startup.
 * - The debug.ini is the main configuration file for RDK Logger and it is intended to be used
 * globally in multi-process environment.
 * - Prints formatted data to stdout.
 * - Separates logs into separate files based on "SEPARATE.LOGFILE.SUPPORT" configuration variable.
 * - RDK logger log files will be generated under "/opt/logs" folder if SEPARATE.LOGFILE.SUPPORT=TRUE
 *
 * @par How to add the RDK logger functionality to the new module?
 * @n Include rdk_debug.h header file and make use of RDK_LOG for printing logs. Initialize RDK Logger by
 * calling rdk_logger_init() in the respective module/component. Build new module/component by linking
 * "librdkloggers.so" along with "liblog4c.so" and "libglib-2.0.so" shared object.
 * @code
 * Example: -lrdkloggers -L ../opensource/lib -llog4c -lglib-2.0
 * @endcode
 *
 * @par RDK Logger Usage
 * @code
 * RDK_LOG (rdk_LogLevel level, const char *module, const char *format,...)
 * @endcode
 * - "level" is Log level of the log message (FATAL, ERROR etc). Apart from this there are
 *    special log levels like ALL, NONE, TRACE, !TRACE are supported.
 * - "module" is the Module to which this message belongs to (Use module name same as mentioned in debug.ini)
 * - "format" is a printf style string containing the log message.
 * @n All the RDK components logs are stored under /opt/log/ with a naming convention <RDK component>_log.txt.
 * @n For example, /opt/log/pod_log.txt includes all events logged by POD Manager module.
 *
 * @par Sample code for Logging:
 * For example, add a debug messages for "INBSI" module
 * @code
 * RDK_LOG (RDK_LOG_NOTICE, "LOG.RDK.INBSI","<%s: %s>: Sending PMT_ACQUIRED event\n", PSIMODULE, __FUNCTION__);
 * @endcode
 * User needs to provide the module name "LOG.RDK.INBSI", which is the same as mentioned in debug.ini
 * @code
 * $ cat debug.ini
 * EnableMPELog = TRUE
 * LOG.RDK.INBSI = ALL FATAL ERROR WARNING NOTICE INFO DEBUG
 * @endcode
 *
 * @par Sample logging output:
 * @code
 * 131011-21:21:49.578394 [mod=INBSI, lvl=NOTICE] [tid=4141] <SITP_PSI: NotifyTableChanged>: Sending PMT_ACQUIRED event
 * @endcode
 * In this way, user make use of the RDK logger in the respective modules and control the logging levels through configuration file.
 * Here, No need to build RDK logger again for the addition of new components/module.
 * @ingroup RDKLOGGER
 *
 * @par How GStreamer logging
 * - A callback function gst_debug_add_log_function() is registered to receive gstreamer logs.
 * - Logs are converted to RDK logs in callback function.
 * - RMF element which controls a gst-element shall register element name and corresponding log module using
 * void RMF_registerGstElementDbgModule(char *gst_module, char *rmf_module)
 * - Callback function uses this information to get module names corresponding to gstreamer logs.
 *
 * @par RDK Logging architecture
 *
 * @image html rdk_logger_architecture.jpg
 *
 * @par RDK Logging Configuration
 * @n Default level of logging is ERROR. Logging settings are configured in debug.ini
 * @code
 * - LOG.RDK.<component1> = FATAL ERROR WARNING NOTICE INFO
 * - LOG.RDK.<component2> = FATAL ERROR WARNING NOTICE INFO DEBUG
 * @endcode
 *
 * @par Logging Levels supported by RDK Logger.
 * Code | Description
 * -----|------------
 * RDK_LOG_FATAL	| Any error that is forcing a shutdown of the service or application to prevent data loss (or further data loss), reserve these only for the most heinous errors and situations where there is guaranteed to have been data corruption or loss.
 * RDK_LOG_ERROR	| Any error which is fatal to the operation but not the service (cant open a file, missing data, etc)
 * RDK_LOG_WARN		| Anything that can potentially cause application oddities, but for which the application automatically recoverring.
 * RDK_LOG_NOTICE	| Anything that largely superfluous for application-level logging.
 * RDK_LOG_INFO		| Generally useful information to log (service start/stop, configuration assumptions, etc).
 * RDK_LOG_DEBUG	| Information that is diagnostically helpful to people more than just developers.
 * RDK_LOG_TRACE1, RDK_LOG_TRACE2,... | Only when it would be "tracing" the code and trying to find one part of a function specifically.
 *
 * @par How log files are upload to server
 * @image html rdk_logupload.jpg
 *
 * @defgroup RDKLOGGER_DEBUG_API RDK Logger APIs
 * Describe the details about RDK debug APIs specifications.
 * @ingroup RDKLOGGER
 *
 * @defgroup RDKLOGGER_UTILS_API RDK Logger Utils APIs
 * Describe the details about RDK Logger utils API specifications.
 * @ingroup RDKLOGGER
 */

/**
* @defgroup rdk_logger
* @{
* @defgroup include
* @{
**/


#ifndef _RDK_DEBUG_H_
#define _RDK_DEBUG_H_

#include <stdio.h>
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @enum rdk_LogLevel
 * @brief These values represent the logging 'levels' or 'types', they are each
 * independent.
 */
typedef enum
{
    ENUM_RDK_LOG_BEGIN = 0, /**< Used as array index. */

    RDK_LOG_FATAL = ENUM_RDK_LOG_BEGIN,
    RDK_LOG_ERROR,
    RDK_LOG_WARN,
    RDK_LOG_NOTICE,
    RDK_LOG_INFO,
    RDK_LOG_DEBUG,

    RDK_LOG_TRACE1,
    RDK_LOG_TRACE2,
    RDK_LOG_TRACE3,
    RDK_LOG_TRACE4,
    RDK_LOG_TRACE5,
    RDK_LOG_TRACE6,
    RDK_LOG_TRACE7,
    RDK_LOG_TRACE8,
    RDK_LOG_TRACE9,

    ENUM_RDK_LOG_COUNT
} rdk_LogLevel;

/**
 * String names that correspond to the various logging types.
 * Note: This array *must* match the RDK_LOG_* enum.
 */
#ifdef RDK_DEBUG_DEFINE_STRINGS
const char *rdk_logLevelStrings[ENUM_RDK_LOG_COUNT] =
{
    "FATAL",
    "ERROR",
    "WARNING",
    "NOTICE",
    "INFO",
    "DEBUG",

    "TRACE1",
    "TRACE2",
    "TRACE3",
    "TRACE4",
    "TRACE5",
    "TRACE6",
    "TRACE7",
    "TRACE8",
    "TRACE9",
};
#else
extern const char *rdk_logLevelStrings[ENUM_RDK_LOG_COUNT];
#endif /* RDK_DEBUG_DEFINE_STRINGS */

/**
 * @ingroup RDKLOGGER_DEBUG_API
 * @{
 */

void rdk_dbg_MsgRaw(rdk_LogLevel level, const char *module,
        const char *format, ...);

/** @} */ //end of Doxygen tag RDKLOGGER_DEBUG_API

/**
 * Use RDK_LOG debug message as.
 * RDK_LOG (rdk_LogLevel level, const char *module, const char *format,...)
 * @param level Log level of the log message
 * @param module Module in which this message belongs to (Use module name same as mentioned in debug.ini)
 * @param format Printf style string containing the log message.
 */

#define RDK_LOG rdk_dbg_MsgRaw


#ifdef __cplusplus
}
#endif

#endif /* _RDK_DEBUG_H_ */


/** @} */
/** @} */

#ifndef _RDK_DEBUG_H_
#define _RDK_DEBUG_H_

#define RDK_LOG_ERROR 0
#define RDK_LOG_INFO  1
#define RDK_LOG_DEBUG 2

typedef int rdk_LogLevel;

void log_rdk(rdk_LogLevel level, const char *module,
        const char *format, ...);

#define RDK_LOG log_rdk

#endif /* _RDK_DEBUG_H_ */

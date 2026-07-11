#ifndef CB_LOGGER_H
#define CB_LOGGER_H

#include "../types.h"

#define LOGGER_WARN_ENABLED 1
#define LOGGER_INFO_ENABLED 1
#define LOGGER_DEBUG_ENABLED 1
#define LOGGER_TRACE_ENABLED 1

// Disable non-production logs in release builds.
#if CB_RELEASE == 1
#define LOGGER_DEBUG_ENABLED 0
#define LOGGER_TRACE_ENABLED 0
#endif

typedef enum {
  LOG_LEVEL_FATAL = 0,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_WARN,
  LOG_LEVEL_INFO,
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_TRACE,
} LogLevel;

b8 logger_init(void);
void logger_shutdown(void);
CB_API void logger_push(LogLevel level, const char *file, u32 line,
                        const char *fmt, ...);

// Fatal-level logging.
#define CB_FATAL(fmt, ...)                                                     \
  logger_push(LOG_LEVEL_FATAL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

// Error-level logging.
#define CB_ERROR(fmt, ...)                                                     \
  logger_push(LOG_LEVEL_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#if LOGGER_WARN_ENABLED == 1

// Warn-level logging.
#define CB_WARN(fmt, ...)                                                      \
  logger_push(LOG_LEVEL_WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define CB_WARN(fmt, ...)
#endif

#if LOGGER_INFO_ENABLED == 1

// Info-level logging.
#define CB_INFO(fmt, ...)                                                      \
  logger_push(LOG_LEVEL_INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define CB_INFO(fmt, ...)
#endif

#if LOGGER_DEBUG_ENABLED == 1
#define CB_DEBUG(fmt, ...)                                                     \
  logger_push(LOG_LEVEL_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define CB_DEBUG(fmt, ...)
#endif

#if LOGGER_TRACE_ENABLED == 1

// Trace-level logging.
#define CB_TRACE(fmt, ...)                                                     \
  logger_push(LOG_LEVEL_TRACE, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define CB_TRACE(fmt, ...)
#endif

#endif

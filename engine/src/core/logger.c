#include "logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANSI_RESET "\033[0m"

static const char *level_colors[] = {
    [LOG_LEVEL_FATAL] = "\033[1m\033[41m", [LOG_LEVEL_ERROR] = "\033[31m",
    [LOG_LEVEL_WARN] = "\033[33m",         [LOG_LEVEL_INFO] = "\033[36m",
    [LOG_LEVEL_DEBUG] = "\033[37m",        [LOG_LEVEL_TRACE] = "\033[90m"};

static const char *level_labels[] = {
    [LOG_LEVEL_FATAL] = "FATAL", [LOG_LEVEL_ERROR] = "ERROR",
    [LOG_LEVEL_WARN] = "WARN",   [LOG_LEVEL_INFO] = "INFO",
    [LOG_LEVEL_DEBUG] = "DEBUG", [LOG_LEVEL_TRACE] = "TRACE"};

b8 logger_init(void) { return true; }
void logger_shutdown(void) {}

void logger_push(LogLevel level, const char *file, u32 line, const char *fmt,
                 ...) {
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char ts[16];
  strftime(ts, sizeof(ts), "%H:%M:%S", tm);

  char message[4096];
  va_list args;
  va_start(args, fmt);
  vsnprintf(message, sizeof(message), fmt, args);
  va_end(args);

  FILE *stream = (level <= LOG_LEVEL_ERROR) ? stderr : stdout;
  fprintf(stream, "%s%s [%s] %s%s \033[90m (%s:%u)" ANSI_RESET,
          level_colors[level], ts, level_labels[level], message, ANSI_RESET,
          file, line);
  
  if (level == LOG_LEVEL_FATAL) {
    fflush(stderr);
    exit(1);
  }
}

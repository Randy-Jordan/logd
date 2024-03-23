#ifndef LOGD_INCLUDED
#define LOGD_INCLUDED


#include <stdio.h>
#include <stdarg.h>

#define UNUSED(x) (void)(x)

// ANSI color escape codes
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLACK "\e[0;30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define BOLD_RED "\x1b[1;91m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"

// ANSI style escape codes
#define ANSI_STYLE_BOLD      "\x1b[1m"
#define ANSI_STYLE_UNDERLINE "\x1b[4m"

enum{LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL,LOG_LEVEL_COUNT};

#define LOGD_TRACE(stream, ...) logd(stream,LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOGD_DEBUG(stream, ...) logd(stream,LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOGD_INFO(stream, ...)  logd(stream,LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define LOGD_WARN(stream, ...)  logd(stream,LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define LOGD_ERROR(stream, ...) logd(stream,LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOGD_FATAL(stream, ...) logd(stream,LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)
void logd(FILE *stream, int level, const char *file, int line, const char *fmt, ...);
#endif

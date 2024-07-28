#ifndef LOGD_INCLUDED
#define LOGD_INCLUDED

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

#define LOGD_VERSION "0.1.0"

// Severity Levels
enum { LVL_TRACE, LVL_DEBUG, LVL_INFO, LVL_WARN, LVL_ERROR, LVL_FATAL, LVL_COUNT };

struct Event {
  va_list args; // Event arguments 
  const char *fmt; // Event argument format
  const char *file; // Filename where event occured
  struct tm *time; // Time event occured (local)
  void *out; // Where event is being output. FILE* fp, int fd, etc. 
  int line; // Line number where event occurent
  int level; // Severity level of the event. 
};
typedef struct Event Event;

typedef void (*log_fn)(Event *ev);
typedef void (*log_lock_fn)(bool lock, void *out);

void log_set_level(int level); // Set global log level
void log_set_quiet(bool toggle);// Turns off/on stderr, will still output to callbacks  
void log_set_colors(bool toggle);// Turns off/on ANSI colors
int log_add_callback(log_fn fn, void *udata, int level); // Add callback
int log_add_fp(FILE *fp, int level);
void logd(int level, const char *file, int line, const char *fmt, ...);

#define LOG_TRACE(...) logd(LVL_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) logd(LVL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)  logd(LVL_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)  logd(LVL_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) logd(LVL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) logd(LVL_FATAL, __FILE__, __LINE__, __VA_ARGS__)

#define UNUSED(x) (void)(x)
#define NOW     time(NULL)

#endif

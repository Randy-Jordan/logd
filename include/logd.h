#ifndef LOGD_INCLUDED
#define LOGD_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define NOW     time(NULL)
#define SEED_PRNG() srand(time(NULL) ^ getpid())
#define BAD_PRNG() srand(1)

// ANSI color escape codes
#define CRESET   "\x1b[0m"
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

enum {LVL_TRACE=0, LVL_DEBUG, LVL_INFO, LVL_WARN, LVL_ERROR,LVL_FATAL,LVL_CNT};
#define LOG_TRACE(...) log_log(LVL_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) log_log(LVL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)  log_log(LVL_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)  log_log(LVL_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_log(LVL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_log(LVL_FATAL, __FILE__, __LINE__, __VA_ARGS__)


struct Event{
  struct tm *time; // Localized time.
  const char *fmt; // Event format string.
  va_list vlist; // Event variable list.
  const char *file; // File where event occurred.
  int line; // Line of file in where event occurred.
  int level; // Global Log Level
  void *udata; // Set the event's output destination
};
typedef struct Event Event;

typedef void (*log_fn)(Event *ev);
typedef void (*log_lock_fn)(bool lock, void *udata);

void log_set_level(int level); // Set global log level
void log_set_quiet(bool enable);// Turns off stderr, will still output to callbacks  
void log_set_colors(bool enable);// Turns on ANSI colors
int log_add_callback(log_fn fn, void *udata, int level); // Add callback
int log_add_fp(FILE *fp, int level);
void log_log(int level, const char *file, int line, const char *fmt, ...);

// Basic Testing Macro
#ifdef DEBUG
#define TEST_FAILED(expr) printf(__DATE__" " __TIME__ " TEST  [%s@%d] " ANSI_COLOR_RED "FAILED %s \n"CRESET, __FILE__, __LINE__, #expr)
#define TEST_PASSED(expr) printf(__DATE__" " __TIME__ " TEST  [%s@%d] " ANSI_COLOR_GREEN "PASSED %s\n"CRESET, __FILE__, __LINE__, #expr)
#define TEST(expr) ((expr) ? TEST_PASSED(expr) : TEST_FAILED(expr))
#else
#define TEST_FAILED(expr)
#define TEST_PASSED(expr)
#define TEST(expr)
#endif

#endif

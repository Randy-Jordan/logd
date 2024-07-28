#ifndef LOGD_INCLUDED
#define LOGD_INCLUDED

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

#define LOGD_VERSION "0.1.0"


// Severity Levels
enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

struct Event {
  va_list args; // Event arguments 
  const char *fmt; // Event argument format
  const char *file; // Filename where event occured
  struct tm *time; // Time event occured (local)
  void *out; // Where event is being output. FILE* fp, int fd, etc. 
  int line; // Line number where event occurent
  int level; // Severity level of the event. 
};
typedef struct Event Ev;

typedef void (*log_fn)(Event *ev);
typedef void (*log_lock_fn)(bool lock, void *out);

void log_set_level(int level); // Set global log level
void log_set_quiet(bool toggle);// Turns off/on stderr, will still output to callbacks  
void log_set_colors(bool toggle);// Turns off/on ANSI colors
int log_add_callback(log_fn fn, void *udata, int level); // Add callback
int log_add_fp(FILE *fp, int level);
void logd(int level, const char *file, int line, const char *fmt, ...);

#define UNUSED(x) (void)(x)
#define NOW     time(NULL)
#define SEED_PRNG() srand(time(NULL) ^ getpid())
#define BAD_PRNG() srand(1)
#define SIZEOF(x)    (ptrdiff_t)sizeof(x)
#define COUNTOF(a)   (sizeof(a) / sizeof(*(a)))
#define LENGTHOF(s)  (countof(s) - 1)

#define FG "3"
#define BR_FG "9"
#define BG "4"
#define BR_BG "10"
#define WITH ";"
#define PLAIN ""
#define BLACK "0"
#define RED "1"
#define GREEN "2"
#define YELLOW "3"
#define BLUE "4"
#define MAGENTA "5"
#define CYAN "6"
#define WHITE "7"
#define ANSI_ESC "\x1b"
#define CRESET   "\x1b[0m"
#define FMT(style) ANSI_ESC "[" style "m"

// Basic Testing Macro
#ifdef DEBUG
#define TEST_FAILED(expr) printf(__DATE__" " __TIME__ " TEST  [%s@%d] " RED "FAILED %s \n"CRESET, __FILE__, __LINE__, #expr)
#define TEST_PASSED(expr) printf(__DATE__" " __TIME__ " TEST  [%s@%d] " GREEN "PASSED %s\n"CRESET, __FILE__, __LINE__, #expr)
#define TEST(expr) ((expr) ? TEST_PASSED(expr) : TEST_FAILED(expr))
#else
#define TEST_FAILED(expr)
#define TEST_PASSED(expr)
#define TEST(expr)
#endif

#endif

#ifndef LOGD_INCLUDED
#define LOGD_INCLUDED

// ANSI color escape codes
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLACK "\e[0;30m"
#define ANSI_COLOR_RED     "\x1b[31m"
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



#endif

# logd 

## Description
A simple logging and testing library written in C. 

## Table of Contents

- [Description](#description)
- [Features](#features) 
- [Usage](#usage)
- [Credits / Resources](#credits--resources)
- [License](#license)

## Features / TODOS

- [ ] User Callbacks for file logging versatility.
- [ ] Logging levels to reduce noise.
- [ ] Optional colors to highlight level and message. 
- [ ] Custom messages and formatting. 
- [ ] Log locking for multithreading.
- [ ] Macros for easy level logging.
- [ ] Quiet mode to disable logging to stderr, will only output to callbacks.

## Usage
There are 6 levels of logging. Set each event and/or log to the level you see fit. Only events >= the global logging level will be logged. 
```
enum { LVL_TRACE, LVL_DEBUG, LVL_INFO, LVL_WARN, LVL_ERROR, LVL_FATAL, LVL_COUNT };
void log_set_level(int level); // Set global log level
void log_set_quiet(bool toggle);// Turns off/on stderr, will still output to callbacks  
int log_add_callback(log_fn fn, void *udata, int level); // Add callback and lvl
int log_add_fp(FILE *fp, int level); // Add file pointer to callbacks
```


Event structure that details file and line where it was called and the local time format. You can set what level the event is, format variables and output, and set the output file where it will be written to.<br>
```
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
``` 

Function like macros for logging. They explicitly set the log level for the event and automatically populate __FILE__ and __LINE__.<br>
```
LOG_TRACE(const char *fmt, ...);
LOG_DEBUG(const char *fmt, ...);
LOG_INFO(const char *fmt, ...);
LOG_WARN(const char *fmt, ...);
LOG_ERROR(const char *fmt, ...);
LOG_FATAL(const char *fmt, ...);
```

Those macros are a wrapper for logd().<br>
```

```


## Credits / Resources
[RXI - log.c](https://github.com/rxi/log.c)<br>
[David Hanson - Interface and Implementations Repo](https://github.com/drh/cii)<br>
[Lexi Hale - On Terminal Control](https://xn--rpa.cc/irl/term.html)<br>


## License
This project is licensed under GPLv3 - see the [LICENSE](LICENSE) file for details.

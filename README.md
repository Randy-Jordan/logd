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
Event structure that details file and line where it was called and the local time format. You can set what level the event is, format variables and output, and set the output file where it will be written to.<br>
```
struct Event{
  struct tm *time; // Localized time not __DATE__ __TIME__
  const char *fmt; // Event format string.
  va_list vlist; // Event variable list.
  const char *file; // File where event occurred.
  int line; // Line of file in where event occurred.
  int level; // Global Log Level
  void *out; // Set the event's output destination. FILE* or fd etc.
};
typedef struct Event Event;
``` 


Function like macros for logging. <br>
```
LOGD_TRACE(const char *fmt, ...);
LOGD_DEBUG(const char *fmt, ...);
LOGD_INFO(const char *fmt, ...);
LOGD_WARN(const char *fmt, ...);
LOGD_ERROR(const char *fmt, ...);
LOGD_FATAL(const char *fmt, ...);
```

## Credits / Resources



## License
This project is licensed under GPLv3 - see the [LICENSE](LICENSE) file for details.

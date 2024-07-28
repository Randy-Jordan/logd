#include "../include/logd.h"
#define MAX_CALLBACKS 32

struct Callback{
    log_fn fn; // Our callback function
    void *out; // Event output ptr
    int level; // Level it will be invoke
};
typedef struct Callback Callback;

static struct {
    void *out; // Log output
    log_lock_fn lock; // Log lock
    int level; // Current logging level
    bool quiet; // Quiete mode
    bool colors; // Colored logs
    Callback callbacks[MAX_CALLBACKS]; // Log event callback
} Log;

static const char *level_colors[] = {
    "\x1b[34m", "\x1b[35m", "\x1b[32m", "\x1b[33m", "\x1b[1;91m","\x1b[31m",
};
static const char *level_strings[] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

static void lock(void)   {
    if (Log.lock) { Log.lock(true, Log.out); }
}
static void unlock(void) {
    if (Log.lock) { Log.lock(false, Log.out); }
}
void log_set_lock(log_lock_fn fn, void *out) {
    Log.lock = fn;
    Log.out = out;
}
void log_set_level(int level) {
    Log.level = level;
}
void log_set_quiet(bool enable) {
    Log.quiet = enable;
}
void log_set_colors(bool enable) {
    Log.colors = enable;
}
int log_add_callback(log_fn fn, void *out, int level) {
    for (int i = 0; i < MAX_CALLBACKS; i++) {
        if (!Log.callbacks[i].fn) {
            Log.callbacks[i] = (Callback) { fn, out, level };
            return 0;
        }
    }
    return -1;
}
static void file_callback(Event *ev) {
char buf[21];
    buf[strftime(buf, sizeof(buf), "%b %d %Y %H:%M:%S", ev->time)] = '\0';
    
    if (Log.colors) {
        fprintf(
            ev->out, "%s %s%-5s\x1b[0m \x1b[90m[%s:%d]\x1b[0m ",
            buf, level_colors[ev->level], level_strings[ev->level],
            ev->file, ev->line);
    } else {
        fprintf(
            ev->out, "%s %-5s [%s@%d] ",
            buf, level_strings[ev->level], ev->file, ev->line);
    }
    
    vfprintf(ev->out, ev->fmt, ev->args);
    fprintf(ev->out, "\n");
    fflush(ev->out); 
}
int log_add_fp(FILE *fp, int level) {
    return log_add_callback(file_callback, fp, level);
}
static void init_event(Event *ev, void *out) {
    if (!ev->time) {
        time_t t = time(NULL);
        ev->time = localtime(&t);
    }
    ev->out = out;
}
static void stdout_callback(Event *ev) {
    char buf[21];
    buf[strftime(buf, sizeof(buf), "%b %d %Y %H:%M:%S", ev->time)] = '\0';
    if(Log.colors == true){
        fprintf(
                ev->out, "%s %s%-5s\x1b[0m \x1b[90m[%s:%d]\x1b[0m ",
                buf, level_colors[ev->level], level_strings[ev->level],
                ev->file, ev->line);
    } else{
        fprintf(
                ev->out, "%s %-5s [%s@%d] ",
                buf, level_strings[ev->level], ev->file, ev->line);}
    vfprintf(ev->out, ev->fmt, ev->args);
    fprintf(ev->out, "\n");
    fflush(ev->out);}
void logd(int level, const char *file, int line, const char *fmt, ...) {
    Event ev = {
        .fmt   = fmt,
        .file  = file,
        .line  = line,
        .level = level,
    };

    lock();

    if (!Log.quiet && level >= Log.level) {
        init_event(&ev, stderr);
        va_start(ev.args, fmt);
        stdout_callback(&ev);
        va_end(ev.args);
    }

    for (int i = 0; i < MAX_CALLBACKS && Log.callbacks[i].fn; i++) {
        Callback *cb = &Log.callbacks[i];
        if (level >= cb->level) {
            init_event(&ev, cb->out);
            va_start(ev.args, fmt);
            cb->fn(&ev);
            va_end(ev.args);
        }
    }

    unlock();
}


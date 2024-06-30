#include "../include/logd.h"
#define MAX_CALLBACKS 32

typedef struct {
    log_fn fn;
    void *udata;
    int level;
} Callback;

static struct {
    void *udata; // Global Data
    log_lock_fn lock; // Set bool lock, and pass data to lock.
    int level;
    bool quiet;
    bool colors;
    Callback callbacks[MAX_CALLBACKS];
} GlobalLogger;

static const char *level_colors[] = {
    ANSI_COLOR_BLUE, ANSI_COLOR_MAGENTA, ANSI_COLOR_GREEN, ANSI_COLOR_YELLOW, BOLD_RED, ANSI_COLOR_RED
};
static const char *level_strings[] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

static void lock(void)   {
    if (GlobalLogger.lock) { GlobalLogger.lock(true, GlobalLogger.udata); }
}
static void unlock(void) {
    if (GlobalLogger.lock) { GlobalLogger.lock(false, GlobalLogger.udata); }
}
void log_set_lock(log_lock_fn fn, void *udata) {
    GlobalLogger.lock = fn;
    GlobalLogger.udata = udata;
}
void log_set_level(int level) {
    GlobalLogger.level = level;
}
void log_set_quiet(bool enable) {
    GlobalLogger.quiet = enable;
}
void log_set_colors(bool enable) {
    GlobalLogger.colors = enable;
}
int log_add_callback(log_fn fn, void *udata, int level) {
    for (int i = 0; i < MAX_CALLBACKS; i++) {
        if (!GlobalLogger.callbacks[i].fn) {
            GlobalLogger.callbacks[i] = (Callback) { fn, udata, level };
            return 0;
        }
    }
    return -1;
}
static void file_callback(Event *ev) {
char buf[21];
    buf[strftime(buf, sizeof(buf), "%b %d %Y %H:%M:%S", ev->time)] = '\0';
    
    if (GlobalLogger.colors) {
        fprintf(
            ev->udata, "%s %s%-5s\x1b[0m \x1b[90m[%s:%d]\x1b[0m ",
            buf, level_colors[ev->level], level_strings[ev->level],
            ev->file, ev->line);
    } else {
        fprintf(
            ev->udata, "%s %-5s [%s@%d] ",
            buf, level_strings[ev->level], ev->file, ev->line);
    }
    
    vfprintf(ev->udata, ev->fmt, ev->vlist);
    fprintf(ev->udata, "\n");
    fflush(ev->udata); 
}
int log_add_fp(FILE *fp, int level) {
    return log_add_callback(file_callback, fp, level);
}
static void init_event(Event *ev, void *udata) {
    if (!ev->time) {
        time_t t = time(NULL);
        ev->time = localtime(&t);
    }
    ev->udata = udata;
}
static void stdout_callback(Event *ev) {
    char buf[21];
    buf[strftime(buf, sizeof(buf), "%b %d %Y %H:%M:%S", ev->time)] = '\0';
    if(GlobalLogger.colors == true){
        fprintf(
                ev->udata, "%s %s%-5s\x1b[0m \x1b[90m[%s:%d]\x1b[0m ",
                buf, level_colors[ev->level], level_strings[ev->level],
                ev->file, ev->line);
    } else{
        fprintf(
                ev->udata, "%s %-5s [%s@%d] ",
                buf, level_strings[ev->level], ev->file, ev->line);}
    vfprintf(ev->udata, ev->fmt, ev->vlist);
    fprintf(ev->udata, "\n");
    fflush(ev->udata);}
void log_log(int level, const char *file, int line, const char *fmt, ...) {
    Event ev = {
        .fmt   = fmt,
        .file  = file,
        .line  = line,
        .level = level,
    };

    lock();

    if (!GlobalLogger.quiet && level >= GlobalLogger.level) {
        init_event(&ev, stderr);
        va_start(ev.vlist, fmt);
        stdout_callback(&ev);
        va_end(ev.vlist);
    }

    for (int i = 0; i < MAX_CALLBACKS && GlobalLogger.callbacks[i].fn; i++) {
        Callback *cb = &GlobalLogger.callbacks[i];
        if (level >= cb->level) {
            init_event(&ev, cb->udata);
            va_start(ev.vlist, fmt);
            cb->fn(&ev);
            va_end(ev.vlist);
        }
    }

    unlock();
}


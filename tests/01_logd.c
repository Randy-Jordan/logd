#define DEBUG

#include "../include/logd.h"
#include <stdlib.h>


int main(void){
    printf("\n\n");
    const char *str = "variable test";
    int num = 7;
    log_add_fp(stdout,LVL_FATAL);
    LOG_TRACE("Testing log trace.");
    log_set_colors(true);
    LOG_DEBUG("Testing log debug and turned on log colors. Debugging str %s and int %d", str,num);
    LOG_INFO("Testing log info, added callback to stdout when level is fatal.Should see two fatal logs.");
    LOG_WARN("Testing log warning");
    LOG_ERROR("Testing log error");
    LOG_FATAL("Testing log fatal");
    printf("\n");
    return EXIT_SUCCESS;
}

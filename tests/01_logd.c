#define DEBUG

#include "../include/logd.h"
#include <stdlib.h>


int main(void){
    printf("\n\n");
    const char *str = "Hello";
    int num = 7;
    log_set_colors(true);
    log_add_fp(stdout,LVL_FATAL);
    LOG_TRACE("Testing log trace.");
    LOG_DEBUG("Testing log debug with str %s and int %d", str,num);
    LOG_INFO("Testing log info");
    LOG_WARN("Testing log warning");
    LOG_ERROR("Testing log error");
    LOG_FATAL("Testing log fatal");
    printf("\n");
    return EXIT_SUCCESS;
}

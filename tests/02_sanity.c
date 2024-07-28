#define DEBUG
#include "../include/logd.h"


int main(void){
    log_set_colors(true);
    LOG_INFO("Sanity Checks");
    TEST(NULL);
    TEST(0 > 1);
    TEST(1 > 0);
}

#define DEBUG
#include "../include/logd.h"


int main(void){
    printf("\n\n");
    TEST(NULL);
    TEST(0 > 1);
    TEST(1 > 0);
}

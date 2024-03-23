#define DEBUG

#include "../include/logd.h"
#include <stdlib.h>


int main(void){
    printf("\n\n");
    LOGD_TRACE(stdout,"Testing log trace.");
    return EXIT_SUCCESS;
}

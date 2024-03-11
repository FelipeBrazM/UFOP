#include "cores.h"

void printErr(char * message){
    printf(RED("%s"), message);
}

void printWarning(char * message){
    printf(YELLOW("%s"), message);
}

void printSuccess(char * message){
    printf(GREEN("%s"), message);
}
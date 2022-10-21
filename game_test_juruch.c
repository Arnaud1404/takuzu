#include <stdbool.h>
#include <stdlib.h>

bool test_dummy(){
    return EXIT_SUCCESS;
}

int main(int argcount, char *argvalue[]){
    if(argcount==1){
        return EXIT_FAILURE;
    }
    if (strcmp("dummy",argvalue[1])==0){
        return EXIT_SUCCESS;
    }
    else{
        return EXIT_FAILURE;
    }
}
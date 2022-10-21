#include <stdbool.h>
#include <stdlib.h>

bool test_dummy(){
    return EXIT_SUCCESS;
}

int main(int argcount, char *argv[]){
    if (strcmp("dummy",argv[1])==0){
        return EXIT_SUCCESS;
    }
    else{
        return EXIT_FAILURE;
    }
}
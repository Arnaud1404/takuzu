#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int test_dummy(void){
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]){
    if (argc == 1){
        return EXIT_FAILURE;
    }
    if (strcmp("dummy",argv[1])==0){
        return test_dummy();
    }
    return EXIT_FAILURE;
}

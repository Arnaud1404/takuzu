#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int test_dummy(void){
    return 0;
}

int main(int argc, char* argv[]){
    if (argc == 1){
        return EXIT_FAILURE;
    }
    if (strcmp("dummy",argv[1])==0){
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

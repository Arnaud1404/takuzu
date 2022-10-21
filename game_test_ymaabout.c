#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


bool test_dummy(void){
    return true;
}

void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}


int main(int argc, char* argv[]){
    if (argc == 1){
        usage(argc,argv);
    }
bool ok = false;
if(strcmp("dummy",argv[1])==0){
    ok = test_dummy();
  
}
if (ok){
    fprintf(stderr, "test: %s success\n", argv[1]);
    return EXIT_SUCCESS;
}
fprintf(stderr, "test: %s failed\n", argv[1]);
return(EXIT_FAILURE);
}
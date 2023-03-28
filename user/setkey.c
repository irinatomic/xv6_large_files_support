#include "user.h"
#include "kernel/types.h"

int main(int argc, char *argv[]){

    int n;
    if(argc == 2)
        n = atoi(argv[1]);
    else
        n = 0;
    setkey(n);
    exit();
}

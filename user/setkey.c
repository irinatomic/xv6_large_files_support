#include "user.h"
#include "kernel/types.h"

char help_meni[] = "--help (-h)    shows help meni\n--secret (-s)  set a key for encr/decr\n";

int main(int argc, char *argv[]){

    if(argc < 2)
        fprintf(2, "Usage: set encr/decr key....\n");

    char *choice = argv[1];

    if(strcmp(choice, "--help") == 0 || strcmp(choice, "-h") == 0)
        fprintf(2, help_meni);
    else if(strcmp(choice, "--secret") == 0 || strcmp(choice, "-s") == 0){
        setecho(0);
        handle_key_input();
        setecho(1);
    }
    exit();
}

void handle_key_input(){

    char buffer[256];
    int len = read(0, buffer, sizeof(buffer));
    buffer[len-1] = '\0';
    int key = atoi(buffer);
    setkey(key);
}

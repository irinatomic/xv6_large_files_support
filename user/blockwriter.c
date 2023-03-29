#include "user.h"
#include "kernel/types.h"
#include "kernel/fcntl.h"

char help_meni[] = 
"--help (-h)                         shows help meni\n\
--output-file (-o) FILENAME         sets the new file name to FILENAME\n\
--blocks (-b) BLOCKS                sets the size of the file in BLOCKS\n";

char str_for_file[512] = 
"Ice cream is a frozen dessert, typically made from milk or cream and flavoured with a sweetener,\
 either sugar or an alternative, and a spice, such as cocoa or vanilla, or with fruit such as strawberries\
 or peaches. It can also be made by whisking a flavored cream base and liquid nitrogen together. Food\
 coloring is sometimes added, in addition to stabilizers. The mixture is cooled below the freezing point\
 of water and stirred to incorporate air spaces and to prevent detectable ice crystals from forming. End.";


int main(int argc, char *argv[]){

    if(argc < 2)
        fprintf(2, "Usage: create new big file up to 8.5MB (1 block = 512 bytes)\n");

    char *choice = argv[1];
    char file_name = "long.txt";
    char size_blocks = 150;

    if(strcmp(choice, "--help") == 0 || strcmp(choice, "-h") == 0)
        fprintf(2, help_meni);
    
    // Get the user input for filename and block size
    for(int i = 1; i < argc; i += 2){
        if(strcmp(choice, "--output-file") == 0 || strcmp(choice, "-o") == 0)
            file_name = argv[i+1];
        else if(strcmp(choice, "--blocks") == 0 || strcmp(choice, "-b") == 0)
            size_blocks = atoi(argv[i+1]);
    }

    // Check the validity of inputs
    if(strlen(file_name) > 14){
        fprintf(2, "Name is too long (up to 14 characters)\n");
        exit();
    }

    if(size_blocks > 16523){
        fprintf(2, "Maxixmum block size is 16523\n");
        exit();
    }

    // Create the file
    // int size_bytes = size_blocks * 512;

    int file_desc = open(file_name, O_CREATE);
    int i = 0;

    while(i < size_blocks){
        int response = write(file_desc, str_for_file, 512);
        if(response != 512){
            printf("Mistake while writing into the file\n");
            exit();
        }

        printf("create block %d\n",i);
		i++;
    }
    

    // if (fd < 0) {
    //     cprintf(2, "creating %s failed\n", file_name);
    //     exit();
    // }

    // //Write 'Hello world' to the file
    // char* str_for_file = "Hello world";
    // int nwritten = write(fd, str_for_file, strlen(str_for_file));
    // if (nwritten < strlen(str_for_file)) {
    //     cprintf(2, "writing 'Hello world' to file failed\n");
    //     close(fd);
    //     exit();
    // }

    // //Fill the rest of the file with null bytes
    // char zeros[size_bytes - strlen(str_for_file)];      // cannot declare aan array of size determined at runtime
    // for (int i = 0; i < sizeof(zeros); i++)             // solution: declare array without initialization
    //     zeros[i] = 0;

    // nwritten = write(fd, zeros, sizeof(zeros));
    // if (nwritten < sizeof(zeros)) {
    //     cprintf(2, "write failed\n");
    //     close(fd);
    //     exit();
    // }

    close(file_desc);
    exit();
}
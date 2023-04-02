#include "user.h"
#include "kernel/types.h"
#include "kernel/fcntl.h"

char help_meni[] = 
"--help (-h)                     shows help meni\n\
--output-file (-o) FILENAME     sets the new file name to FILENAME (long.txt)\n\
--blocks (-b) BLOCKS            sets the size of the file in BLOCKS (150)\n";

char str_for_file[] = 
"Ice cream is a frozen dessert, typically made from milk or cream and flavoured with a sweetener,\
 either sugar or an alternative, and a spice, such as cocoa or vanilla, or with fruit such as strawberries\
 or peaches. It can also be made by whisking a flavored cream base and liquid nitrogen together. Food\
 coloring is sometimes added, in addition to stabilizers. The mixture is cooled below the freezing point\
 of water and stirred to incorporate air spaces and to prevent detectable ice crystals from forming.\0";

int main(int argc, char *argv[]){

    char *choice = argv[1];
    char *file_name = "long.txt";
    int size_blocks = 150;

    if(argc < 2 || strcmp(choice, "--help") == 0 || strcmp(choice, "-h") == 0){
        fprintf(2, help_meni);
        exit();
    }
    
    // Get the user input for filename and block size
    for(int i = 1; i < argc; i += 2){
        choice = argv[i];
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
    // 0x200 creates file
	// 0x002 opens file for read and write

    int file_desc = open(file_name, 0x200|0x002);
    int i = 0;
    while(i < size_blocks){   
        int response = write(file_desc, str_for_file, 512);
        if(response != 512){
            fprintf(2, "Mistake while writing into the file %d\n", i);
            exit();
        }

        printf("create block %d\n", i);
		i++;
    }

    close(file_desc);
    exit();
}
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

char help_meni[] = 
"--help (-h)           xshows help meni\
--encrypt-all (-a)    encrypts all files in the current dir";

void format_response(int response){
    
    switch(response){
        case -1: printf("encription key is not set"); break;
        case -2: printf("cannot encrypt T_DEV"); break;
        case -3: printf("file is already encrypted"); break;
        case 0: printf("file successfully encrypted"); break;
        default: printf("error");
    }
}

void encrypt_all_files(){

    // char buf[512], *p;
    // int curr_dir;
    // struct dirent de;               // directory entity (file or dir)
    // struct stat st;                 // contains info about the file 

    // if((curr_dir = open(".", 0)) < 0){
	// 	fprintf(2, "cannot open current working dir\n");
	// 	return;
	// }

    // if(fstat(curr_dir, &st) < 0){
	// 	fprintf(2, "cannot stat current working dir\n");
	// 	close(curr_dir);
	// 	return;
	// }

    // strcpy(buf, curr_dir);
    // p = buf + strlen(buf);
    // *p++ = '/';
    // while(read(curr_dir, &de, sizeof(de)) == sizeof(de)){
    //     if(de.inum == 0)
    //         continue;

    //     memmove(p, de.name, DIRSIZ);
    //     p[DIRSIZ] = 0;
    //     if(stat(buf, &st) < 0){
    //         printf("ls: cannot stat %s\n", buf);
    //         continue;
    //     }

    //     char* name = fmtname(buf);
    //     if(st.type != T_DIR){
    //         int fd = open(name, 0x200 | 0x002);
    //         int response = encr(fd);
    //         format_response(response);
    //     }
	// }

    // close(curr_dir);
}

void encrypt_file(char* file_name){

    int fd = open(file_name, 0x200 | 0x002);
    int response = encr(fd);
    format_response(response);
    close(fd);
}

int main(int argc, char *argv[]){

    if(argc < 2 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
        fprintf(2, help_meni);

    if(strcmp(argv[1], "--encrypt-all") == 0 || strcmp(argv[1], "-a") == 0)
        encrypt_all_files();
    else
        encrypt_file(argv[1]);

    exit();
}
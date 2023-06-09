#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char help_meni[] = 
"--help (-h)           shows help meni\n\
--encrypt-all (-a)    encrypts all files in the current dir\n";

void format_response(int response){
    
    switch(response){
        case -1: fprintf(2, "encription key is not set\n"); break;
        case -2: fprintf(2, "cannot encrypt T_DEV\n"); break;
        case -3: fprintf(2, "file is already encrypted\n"); break;
        case 0: fprintf(2, "file successfully encrypted\n"); break;
        default: fprintf(2, "error in some helper function\n");
    }
}

void encrypt_all_files(){

    char *path = ".";                           // working in current dir
    char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;

	if((fd = open(path, 0)) < 0){               //check if we can open
		fprintf(2, "encr: cannot open\n");
		return;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "encr: cannot stat\n");
		close(fd);
		return;
	}

	strcpy(buf, path);                 // code taken from ls.c for listing files in curr dir
	p = buf + strlen(buf);
	*p++ = '/';

	while(read(fd, &de, sizeof(de)) == sizeof(de)){
		if(de.inum == 0)
			continue;
		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
		if(stat(buf, &st) < 0){
			fprintf(2, "encr: cannot stat\n");
			continue;
		}


        if(st.type == T_FILE){
            encrypt_file(buf);				// do not want to print response so we don't stop the code execution
        }
	}
	
	close(fd);
}

void encrypt_file(char* path){

    int fd;
	if((fd = open(path, O_RDWR)) < 0)
		fprintf(2, "encr: Failed to open\n");
	
	encr(fd);				// calls the sys interrupt sys_encr
	close(fd);
}

int main(int argc, char *argv[]){

    if(argc < 2 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0){
        fprintf(2, help_meni);
        exit();
    }

    if(strcmp(argv[1], "--encrypt-all") == 0 || strcmp(argv[1], "-a") == 0)
        encrypt_all_files();
    else
        encrypt_file(argv[1]);

    exit();
}
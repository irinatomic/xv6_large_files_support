#include "types.h"
#include "defs.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "encription.h"

int encript(char *buf){
	char *a = buf;
	uint i = 0;

	while(*a != '\0'){
		*a= (char) ((((int) *a) + encription_key) % 255);		// ascii table size is 255
		a++;
		i++;
	}
	return i;
}

int decript(char *buf){
	char *a = buf;
	uint i = 0;
	
	while(*a != '\0'){
		int new_val = ((int) *a) - encription_key;
		if(new_val < 0)
			new_val += 256;
		*a = (char) (new_val % 255);		
		a++;
		i++;
	}
    return i;
}

int file_encr_decr(struct file *f, int encr){
	
	if(f->readable == 0)
		return -1;	
	
	int r;
	char buf[512];
	uint re = f->off, wr = f->off;

    cprintf("5");

	while((r = fileread(f, buf, sizeof(buf))) > 0){
		if(encr == 1){
            encript(buf);
        } else {
            decript(buf);
        }

        cprintf("6");
		re = f->off;;
		f->off = wr;
		if (filewrite(f, buf, r) != r) 
			return -1;
			
        cprintf("7");
		wr = f->off;
		f->off = re;
	}

    cprintf("8");

    // transaction -> write block to disk
	begin_op();					
	ilock(f->ip);
    if(encr){
	    (f->ip)->major = 1;				// set the major flag to 1 (encripted)
    } else{
        (f->ip)->major = 0;				// set the major flag to 0 (not encripted)
    }
	iupdate(f->ip);
	iunlock(f->ip);
	end_op();
	return 0;
}
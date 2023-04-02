#include "types.h"
#include "defs.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "encription.h"

void encript(char *buf){
	char *a = buf;
	uint i = 0;

	while(*a != '\0'){
		*a= (char) ((((int) *a) + encription_key) % 255);		// ascii table size is 255
		a++;
		i++;
	}
}

void decript(char *buf){
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
}

int file_encr_decr(struct file *f, int encr){
	
	if(f->readable == 0)
		return -1;	
	
	int r;
	char buf[512];

	int size = (int)f->ip->size;
	int num_blocks = size / 512;

	for(int i = 0; i < num_blocks; i++){
		r = fileread(f, buf, sizeof(buf));
		if(encr == 1){
            encript(buf);
         } else {
            decript(buf);
         }

		f->off = 512 * i;
		if (filewrite(f, buf, r) != r) 
			return -1;
	}

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
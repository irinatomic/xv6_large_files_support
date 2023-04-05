## Homework 2 for Uni

The purpose of this homework was to improve an xv6 operating system by making a spport for a large file system (double indirect inode) and encrypt files using Cesaeran cypher.

Following user and system calls were to be implemented:
| User call | System call |
|--|--|
| blockwriter | / |
|encr|int encr (int fd)|
|decr|int decr (int fd)|
|setkey|void setkey(int key), int setecho (int echo)|

### Double indirect inode
Change the inode (both inode and dinode) structure to support double indirect pointer to blocks. After the change, one file should be able to consist of 11 + 128 + 128 * 128 blocks. 

The changes can be seen in fs.h (struct dinode - represents file on disc) and file.h (struct inode - represents file in the system). Allocating necessary physical blocks for extra logical ones can be seen in fs.c (bmap function). Freeing up disk space when deleting extra blocks can be seen in fs.c (itrunc function).

### Encription and decription
The Caesar code is used for encryption purposes. This code requires setting one int number as the key for encryption and decryption, and should work for all characters in the ASCII table. The setting of this key is done using a **system call setkey**, and the key is global at the level of the entire operating system. The key is always a positive number or zero. Any user program can make this call to change the **global key**. Once the key is set, a file already on disk can be encrypted or decrypted using the encr and decr system calls. Both system calls expect the file to be already open for reading and writing. 

In addition, it is necessary to change the behavior of read/write system calls (in sysfile.c) so that they automatically decrypt/encrypt when reading/writing. 

The files will have the encryption information recorded in the major attribute in the inode structure: 0 means that the file is not encrypted, and 5 means that it is. These operations use a globally set decryption/encryption key. If the wrong key is used when reading the file, it is expected that meaningless text will be obtained as a result of reading.

### User programs
**1. Blockwriter**
Creates a new file in current directory (default values - name: long.txt, block size: 150). User can change these:  `blockwriter -b BLOCKS -o FILENAME`.
If no arguments are given, a help menu is displayed:

    --help (-h) shows help meni
    --output-file (-o) FILENAME sets the new file name to FILENAME (long.txt)
    --blocks (-b) BLOCKS sets the size of the file in BLOCKS (150)

**2. Setkey**
Setkey sets the system key to a value using a system call setkey, which is entered via command line parameters or via STDIN.

    --help (-h) shows help meni
    --secret (-s) set a key for encr/decr

**3. Encr**
Encr encrypts one or more files by calling the encr system call. If the encryption file name is omitted, print the help menu. The logic bhind this can be seen in user/encr.c and kernel/encription.c file.

    --help (-h) shows help meni
    --encrypt-all (-a) encrypts all files in the current dir

**4. Decr**
Decr decrypts one or more files by calling the decr system call. If the decryption file name is omitted, print the help menu. The logic bhind this can be seen in user/decr.c and kernel/encription.c file.

    --help (-h) shows help meni
    --decrypt-all (-a) decrypts all files in the current dir

## Important - Makefile is for M1 Macs
Makefile given in this repo is the one one configured so the xv6 works on Macs <br> 
with M1 chip. After cloning this repo to M1 Mac, run these commands in terminal: <br>
`brew install qemu` <br>
`brew install x86_64-elf-gcc`

Create a .bash_profile that contains additional variables for running xv6. <br>
`cd ~/` <br>
`touch .bash_profile` <br>
`open -e .bash_profile` 

Add these commands to your .bash_profile file: <br>
`export TOOLPREFIX=x86_64-elf- ` <br>
`export QEMU=qemu-system-x86_64`

Finally, run the file: <br>
`source .bash_profile`

After cmpleting this, you can go into the cloned repo and start the xv6 with <br>
`make qemu`
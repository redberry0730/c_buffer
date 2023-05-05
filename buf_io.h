#ifndef BUF_IO_H
#define BUF_IO_H

#define BUF_SIZE 4096

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


// define a new bfile (for buffered file) type
typedef struct _bfile
{
    // TODO: fill me in
    // you'll need to add whatever fields are necessary
    // here to buffer and track the buffer for one file
    size_t fd;
    char *buffer;
    char *name;
    char *location; 
} bfile;

// buffered open; open filename for reading
bfile *bopen(char *filename);

// buffered read; read num_bytes into userbuf from file
int bread(bfile *file, char *userbuf, size_t num_bytes);

// buffered close; close file
int bclose(bfile *file);

#endif

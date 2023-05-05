#include <stdlib.h>
#include <stdio.h>
// TODO: add whatever other header files you need

#include "buf_io.h"

// open filename for reading
bfile *bopen(char *filename)
{
    // TODO: fill me in
    // you'll need to create and return a bfile variable and
    // initialize it's component variables accordingly

    char *buf = (char *)malloc(BUF_SIZE*sizeof(char));
    if (buf == NULL) {
        printf("Error: out of memory\n");
	exit(1);
    }

    bfile *bp = (bfile *)malloc(sizeof(bfile));
    bp -> name = filename;
    bp -> fd = open(filename, 0);
    bp -> buffer = buf;
    bp -> location = buf;
    
    if (bp->fd == -1) {
	printf("%s: no such file or directory\n", bp->name);
	exit(1);
    }

    return bp;
}

// buffered read; read num_bytes into userbuf from file
int bread(bfile *file, char *userbuf, size_t num_bytes)
{
    // TODO: fill me in
    // the bulk of the work goes here
    // you need to copy data from your internal buffer to
    // userbuf; if you don't have enough data in the internal
    // buffer, then call read() to get more, BUF_SIZE bytes
    // at a time
    // be sure to think through all cases carefully
   
    if (file == NULL || userbuf == NULL || num_bytes < 1) {
        exit(1);
    }

    //if the requested size is bigger than the size of the buffer
    if (num_bytes >= BUF_SIZE) {
        int i = read(file->fd, userbuf, num_bytes);
	return i;
    }
    else {
	//if the pointer is at the beginning of the buffer, fill the buffer
	if (file->location == file->buffer) {
	    int check_buff = read(file->fd, file->buffer, BUF_SIZE);
	    //check whether read is working
	    if (check_buff == -1) {
		printf("Error in check_buff");
		exit(1);
	    }
	    //check when the end of the file is reached
	    else if (check_buff == 0) {
		return check_buff;
	    }
	}
	//if the requested size is bigger than the space left in the buffer,
	//copy the remaining space to the user buffer and reset the pointer
	if (file->location + num_bytes >= file->buffer + BUF_SIZE) {
	     int byte_tracker = (file->buffer + BUF_SIZE) - file->location;
	     memcpy(userbuf, file->location, byte_tracker);
	     file->location = file->buffer;
	     return byte_tracker;
	}
	//if there's enough space in the buffer for the requested size
	else {
	    memcpy(userbuf, file->location, num_bytes);
	    file->location += num_bytes;
	    return num_bytes;
	}
    }
    
    //If bread doesn't hit any of the loops above
    printf("Error in bread");
    return 0;
}

// buffered close; close file
int bclose(bfile *file)
{
    // TODO: fill me in
    // close the file and clean up your memory
    
    if(close(file->fd) != 0) {
        printf("%s: close error\n", file->name);
    }  

    free(file->buffer);
    free(file);

    return 0;
}

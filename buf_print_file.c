#include <stdio.h>
#include <stdlib.h>
#include "buf_io.h"

// TODO: fill me in
// this program should work exactly like print_file, except
// that it will call bopen(), bread() and bclose() instead

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s filename bytes_per_read\n", basename(argv[0]));
        exit(1);
    }

    int bytes_per_read = atoi(argv[2]);
    if (bytes_per_read < 1){
        printf("error: must read at least one byte per iteration\n");
        printf("usage: %s filename bytes_per_read\n", basename(argv[0]));
        exit(1);
    }

    bfile *file = bopen(argv[1]);

    char *buf = (char *)malloc((bytes_per_read+1)*sizeof(char));
    if (buf == NULL)
    {
        // always check for errors!
	printf("error: out of memory\n");
        exit(1);
    }
        
    int read_return = 0;
    while ((read_return = bread(file, buf, bytes_per_read)) >= 1)
    {
        // add the null terminator so that we can print the
        //         // array as a C-string
        buf[read_return] = '\0';
        printf("%s", buf);
    }

    if (read_return == -1) {
	printf("%s: read error\n", argv[1]);
	exit(1);
    }

    bclose(file);
    free(buf);  

    return 0;
}

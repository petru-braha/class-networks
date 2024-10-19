#ifndef _0COMMON0_
#define _0COMMON0_

// header files
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <string.h>
#include <errno.h>

// preprocessed methods
#define print_function_name(x) printf("\"%s\"", #x);

#define call(x) if(x < 0) { \
    printf("line %d error: ", __LINE__); print_function_name(x); \
    printf(" failed - %s.\n", strerror(errno)); \
    exit(EXIT_FAILURE); \
}

// constants
const char fifo_file_name[] = "client-server-fifo";

#endif

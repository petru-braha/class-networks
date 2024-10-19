#include <utmp.h>
#include "apps.h"

void login();
void get_logged_users();
void get_proc_info();
void logout();
void quit();

// first to run
int main()
{
    // fifo
    if(-1 == mknod(fifo_file_name, __S_IFIFO | 0777, 0))
        if(EEXIST != errno)
            exit(EXIT_FAILURE);

    int fd = 0;
    
    call(fd = open(fifo_file_name, O_RDONLY));

    char* line = 0;
    size_t line_size = 0;
    
    // read
    
}

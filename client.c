
#include "apps.h"

// second to run
int main()
{
    // ux
    unsigned int commands_number = 0;
    call(printf("type commands' number: "));
    call(scanf("%u", &commands_number));
    call(scanf("\n"));
    
    int fd = 0;
    call(fd = open("client-server-fifo", O_WRONLY));

    // read command - line and send
    for(unsigned int i = 0; i < commands_number; i++)
    {
        char* line = 0;
        size_t line_size = 0;
        call(getline(&line, &line_size, stdin));
        write(fd, line, line_size);
    }

    // print on screen result of a command
}

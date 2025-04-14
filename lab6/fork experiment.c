#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// hypothesis: 
// the child process does not execute all the instructions 
// before the fork and only inherets the data
    
int main()
{
    char buffer[] = "message";
    printf("%s\n", buffer);
    
    pid_t pid = fork();
    if(0 == pid)
    {
        printf("%s\n", buffer); 
        exit(EXIT_SUCCESS);
    }

    return 0;
}

// 23 line proves that my hypothesis is true 

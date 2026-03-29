#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 


#define READ 0
#define WRITE 1 

// make birectional communication

int main() 
{
    int pipe_fds[2];  
    pipe(pipe_fds);

    pid_t pid = fork(); 
    if(pid > 0) { // parent

        write(pipe_fds[WRITE], "stuff", 5);

    } else { // child

        char buff[10];
        int len_read = read(pipe_fds[READ], buff, 5);
        buff[len_read] = '\0';

        printf("child - received: \"%s\".\n", buff);
        
        const char message[] = "read from parent.\n";
        write(pipe_fds[WRITE], message, strlen(message));
    }


    char message[30] = "";
    read(pipe_fds[READ], message, strlen(message));

    printf("parent - received: \"%s\".\n", message);
    // trebuie 2 pipe uri ca sa transport inapoi
} 

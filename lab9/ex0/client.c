#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

const int COUNT_CHARACTER_MAX = 48;

void error()
{
    printf("error at %d: %s",__LINE__, strerror(errno));
    exit(EXIT_FAILURE);
}

int main()
{
    char ip_address[COUNT_CHARACTER_MAX];
    //strcpy(ip_address, "13.81.174.116");
    strcpy(ip_address, "127.0.0.1");
    
    const uint16_t port = 2900;

    // socket
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sd)
        error();

    // server address
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip_address); 
    server.sin_port = htons(port);

    if(-1 == connect(sd, (struct sockaddr*)&server, sizeof(server)))
        error();
    
    // send
    const char data[] = "braha:petru:2e3";
    const int data_size = strlen(data);
    if(-1 == write(sd, &data_size, sizeof(data_size)))
        error();
    if(-1 == write(sd, data, 16))
        error();
    
    close(sd);
    return 0;
}

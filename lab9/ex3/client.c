#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

const int COUNT_CHARACTER_MAX = 48;

#define error()\
{\
    printf("error at %d: %s", __LINE__, strerror(errno));\
    exit(EXIT_FAILURE);\
}

const int port0 = 2910;
const int port1 = 2911;

int main()
{
    // socket
    int sd0 = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sd0)
        error();
    int sd1 = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sd1)
        error();

    // server address
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    server.sin_port = htons(port0);
    if (-1 == connect(sd0, (struct sockaddr *)&server, sizeof(server)))
        error();
    
    server.sin_port = htons(port1);
    if (-1 == connect(sd1, (struct sockaddr *)&server, sizeof(server)))
        error();

    // write server
    int nr = 5;
    if (-1 == write(sd0, &nr, sizeof(nr)))
        error();
    if (-1 == write(sd1, &nr, sizeof(nr)))
        error();
    if (-1 == write(sd0, &nr, sizeof(nr)))
        error();
    if (-1 == write(sd1, &nr, sizeof(nr)))
        error();

    close(sd0);
    close(sd1);
    return EXIT_SUCCESS;
}

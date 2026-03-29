#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define error()                                               \
    {                                                         \
        printf("error at %d: %s", __LINE__, strerror(errno)); \
        exit(EXIT_FAILURE);                                   \
    }

const int port0 = 2910;
const int port1 = 2911;

int main()
{
    // socket
    int sd_tcp = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sd_tcp)
        error();
    int sd_udp = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sd_udp)
        error();

    // server address
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    server.sin_port = htons(port0);
    if (-1 == connect(sd_tcp, (struct sockaddr *)&server, sizeof(struct sockaddr)))
        error();

    server.sin_port = htons(port1);
    //if(-1 == bind(sd_udp, (struct sockaddr *)&server, sizeof(struct sockaddr)))
        //error();
    //if (-1 == connect(sd_udp, (struct sockaddr *)&server, sizeof(struct sockaddr)))
        //error();

    // write server
    int nr = 5;
    if (-1 == write(sd_tcp, &nr, sizeof(nr)))
        error();
    if (-1 == sendto(sd_udp, &nr, sizeof(nr), 0, (struct sockaddr *)&server, sizeof(struct sockaddr)))
        error();
    if (-1 == write(sd_tcp, &nr, sizeof(nr)))
        error();
    if (-1 == sendto(sd_udp, &nr, sizeof(nr), 0, (struct sockaddr *)&server, sizeof(struct sockaddr)))
        error();

    close(sd_tcp);
    close(sd_udp);
    return EXIT_SUCCESS;
}

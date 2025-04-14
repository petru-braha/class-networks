#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

const int port0 = 2910;
const int port1 = 2911;

#define error()                                               \
    {                                                         \
        printf("error at %d: %s", __LINE__, strerror(errno)); \
        exit(EXIT_FAILURE);                                   \
    }

int main()
{
    int sd0 = 0, sd1 = 0;
    sd0 = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sd0)
        error();
    sd1 = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sd1)
        error();

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    server.sin_port = htons(port0);
    if (-1 == bind(sd0, (struct sockaddr *)&server, sizeof(struct sockaddr)))
        error();

    printf("am ajuns aici.\n");

    server.sin_port = htons(port1);
    if (-1 == bind(sd1, (struct sockaddr *)&server, sizeof(struct sockaddr)))
        error();

    printf("am ajuns aici.\n");

    if (-1 == listen(sd0, 1))
        error();
    if (-1 == listen(sd1, 1))
        error();

    printf("am ajuns aici.\n");

    struct sockaddr_in skadd_client;
    socklen_t length = sizeof(skadd_client);
    bzero(&skadd_client, length);

    int sd_client0 = accept(sd0, (struct sockaddr *)&skadd_client, &length);
    length = sizeof(skadd_client);
    int sd_client1 = accept(sd1, (struct sockaddr *)&skadd_client, &length);
    if (-1 == sd_client0 || -1 == sd_client1)
        error();

    int nr = 0;
    read(sd_client0, &nr, sizeof(nr));
    printf("%d", nr);
    read(sd_client1, &nr, sizeof(nr));
    printf("%d", nr);
    read(sd_client0, &nr, sizeof(nr));
    printf("%d", nr);
    read(sd_client1, &nr, sizeof(nr));
    printf("%d", nr);

    close(sd_client0);
    close(sd_client1);
    close(sd0);
    close(sd1);

    printf("is here any error? : %s.\n", strerror(errno));

    return 0;
}

/* In the TCP/IP protocol stack, a socket is identified by a unique combination of an IP address and a port number. */
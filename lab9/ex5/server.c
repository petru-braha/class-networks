#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

const int port0 = 2910;

#define error()                                               \
    {                                                         \
        printf("error at %d: %s", __LINE__, strerror(errno)); \
        exit(EXIT_FAILURE);                                   \
    }

int main()
{
    int sd_tcp = 0, sd_udp = 0;
    sd_tcp = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sd_tcp)
        error();
    sd_udp = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sd_udp)
        error();

    int opt = 1;
    setsockopt(sd_tcp, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt(sd_udp, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port0);

    if (-1 == bind(sd_tcp, (struct sockaddr *)&server, sizeof(struct sockaddr)))
        error();

    if (-1 == bind(sd_udp, (struct sockaddr *)&server, sizeof(struct sockaddr)))
        error();

    if (-1 == listen(sd_tcp, 1))
        error();

    socklen_t leen_udp = sizeof(struct sockaddr);
    struct sockaddr_in skadd_client;
    socklen_t length = sizeof(skadd_client);
    bzero(&skadd_client, length);

    // tcp
    int sd_client0 = accept(sd_tcp, (struct sockaddr *)&skadd_client, &length);
    if (-1 == sd_client0)
        error();

    int nr = 0;
    read(sd_client0, &nr, sizeof(nr));
    printf("%d ", nr);
    recvfrom(sd_udp, &nr, sizeof(nr), 0, (struct sockaddr *)&server, &leen_udp);
    printf("%d ", nr);
    read(sd_client0, &nr, sizeof(nr));
    printf("%d ", nr);
    recvfrom(sd_udp, &nr, sizeof(nr), 0, (struct sockaddr *)&server, &leen_udp);
    printf("%d ", nr);

    close(sd_client0);
    close(sd_tcp);
    close(sd_udp);

    printf("\nis here any error? : %s.\n", strerror(errno));

    // extra
    sd_udp = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == bind(sd_udp, (struct sockaddr *)&server, sizeof(struct sockaddr)))
        error();
    recvfrom(sd_udp, &nr, sizeof(nr), 0, (struct sockaddr *)&server, &leen_udp);
    printf("%d ", nr);

    close(sd_udp);
    return 0;
}

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

const int COUNT_CHARACTER_MAX = 48;

void error()
{
    printf("error at %d: %s", __LINE__, strerror(errno));
    exit(EXIT_FAILURE);
}

int main()
{
    // socket
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sd)
        error();

    // server address
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(2900);

    if (-1 == connect(sd, (struct sockaddr *)&server, sizeof(server)))
        error();

    // operation
    int nr0 = -1;
    int nr1 = -1;
    char op = '+';

    printf("choose two int numbers and a char operation.\n");

    // read keyboard
    if (-1 == scanf("%d", &nr0))
        error();
    if (-1 == scanf("%d", &nr1))
        error();
    
    // write server
    if (-1 == write(sd, &nr0, sizeof(nr0)))
        error();
    if (-1 == write(sd, &nr1, sizeof(nr1)))
        error();
    if (-1 == write(sd, &op, sizeof(op)))
        error();

    // receive server
    int nr2 = -1;
    read(sd, &nr2, sizeof(nr2));
    printf("the expected result is %d.\n", nr0 + nr1);
    printf("the obtained result is %d.\n", nr2);

    close(sd);
    return EXIT_SUCCESS;
}
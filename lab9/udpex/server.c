/* servTCPIt.c - Exemplu de server UDP
   Asteapta un nume de la clienti; intoarce clientului sirul
   "Hello nume".

   Autor: Lenuta Alboaie  <adria@info.uaic.ro> (c)
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <arpa/inet.h>

/* portul folosit */
#define PORT 2728

/* codul de eroare returnat de anumite apeluri */
extern int errno;

int main()
{
    struct sockaddr_in server; // structura folosita de server
    struct sockaddr_in client;
    char msg[100];           // mesajul primit de la client
    char msgrasp[100] = " "; // mesaj de raspuns pentru client
    int sd;                  // descriptorul de socket

    /* crearea unui socket */
    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("[server]Eroare la socket().\n");
        return errno;
    }

    bzero(&server, sizeof(server));
    bzero(&client, sizeof(client));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("[server]Eroare la bind().\n");
        return errno;
    }

    /* it is concurrent */
    for (;;)
    {
        int msglen;
        int length = sizeof(client);
        
        // check the address
        printf("\n%s:%d.\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        
        printf("[server] wait message.\n");
        msglen = recvfrom(sd, msg, 100, 0, (struct sockaddr *)&client, &length);
        printf("[server] received message.\n");

        // check the address
        printf("\n%s:%d.\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        
        int pid = fork();
        if (0 == pid)
        {
            bzero(msgrasp, 100);
            strcat(msgrasp, "Hello ");
            strcat(msgrasp, msg);

            if (sendto(sd, msgrasp, 100, 0, (struct sockaddr *)&client, length) <= 0)
                exit(1);
            printf("[server]Mesajul a fost trasmis cu succes: %s.\n", msg);
            exit(0);
        }
    }
}

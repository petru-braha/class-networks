/* cliTCPIt.c - Exemplu de client TCP
   Trimite un nume la server; primeste de la server "Hello nume".

   Autor: Lenuta Alboaie  <adria@info.uaic.ro> (c)
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

int main()
{
  int sd;                    // descriptorul de socket
  struct sockaddr_in server; // structura folosita pentru conectare
  char msg[100];             // mesajul trimis

  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Eroare la socket().\n");
    return errno;
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("10.100.0.30");
  uint16_t port = 49160; 
  server.sin_port = htons(port);

  /* ne conectam la server */
  if (connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
  {
    perror("[client]Eroare la connect().\n");
    return errno;
  }

  /* citirea mesajului */
  bzero(msg, 100);
  printf("[client]Introduceti un nume: ");
  fflush(stdout);
  read(0, msg, 100);

  /* trimiterea mesajului la server */
  if (write(sd, msg, 100) <= 0)
  {
    perror("[client]Eroare la write() spre server.\n");
    return errno;
  }

  /* citirea raspunsului dat de server
     (apel blocant pina cind serverul raspunde); Atentie si la cum se face read- vezi cursul! */
  if (read(sd, msg, 100) < 0)
  {
    perror("[client]Eroare la read() de la server.\n");
    return errno;
  }
  /* afisam mesajul primit */
  printf("[client]Mesajul primit este: %s\n", msg);

  /* inchidem conexiunea, am terminat */
  close(sd);
}
//refer http://cs241.cs.illinois.edu/wikibook/networking-part-3-building-a-simple-tcp-client.html
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int s;

    

    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 only */
    hints.ai_socktype = SOCK_STREAM; /* TCP */ /* SOCK_DGRAM is for UDP */

    //transfer the
    s = getaddrinfo("www.google.com", "80", &hints, &result);
    if (s != 0)
    {
        printf("error to get addrinfo, return value %d\n", s);
        exit(1);
    }

    struct addrinfo *p;
    char host[256];

    for (p = result; p != NULL; p = p->ai_next)
    {

        getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
        printf("hostip: (%s)\n", host);
    }

                /*
int socket (int domain, int type, int ptotocol)
return nonnegatice descriptor if ok, -1 or error

AF_INET: internetwork: UDP, TCP, etc.

SOCK_STREAM: based on TCP

protocol: always 0 for non-zero , refer to LPI(56.1)

the sock_fd is only partial opened and cannot yet be used for reading and writing
how we finish the socket depends on whether we are client or a server
*/
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    
    /*
    int connect(int sockfd, struct sockaddr *serv_addr, int addrlen)
    return 0 if ok, -1 if error

    establish an Internet connection with the server at socket address aerv_addr
    */

    // connect the first one in the result linked list here
    // similar to use command "curl" here
    

    if (connect(sock_fd, result->ai_addr, result->ai_addrlen) == -1)
    {
        perror("connect error");
        exit(2);
    }





    //printf("socket src (%s) dst (%s)\n",)
    // use these string means sending http request here
    char *buffer = "GET / HTTP/1.0\r\n\r\n";
    printf("SENDING: %s", buffer);
    printf("===\n");

    // For this trivial demo just assume write() sends all bytes in one go and is not interrupted
    // the operation here is similar like reading or writing materials from a file direactly
    // there is no buffer if using write function direactly
    // serch for buffered io in c for more details
    // or refer to http://csapp.cs.cmu.edu/3e/ics3/code/include/csapp.h to find a example of a robust I/O (Rio) package

    write(sock_fd, buffer, strlen(buffer));

    char resp[10000];
    int len;
    while (1)
    {
        len = read(sock_fd, resp, 999);
        if (len <= 0)
        {
            break;
        }
        printf("%s\n", resp);
    }
    

    close(sock_fd);

    return 0;
}
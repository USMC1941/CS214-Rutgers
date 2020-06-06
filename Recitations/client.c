/*
    C ECHO client example using sockets
    http://www.binarytides.com/server-client-example-c-sockets-linux/
*/
#include <stdio.h>      //printf
#include <string.h>     //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h>  //inet_addr
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];

    // Create socket
    // SOCK_STREAM is for TCP SOCK_DGRAM is for UDP
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    // set the address of the server, protocol, server addr, port
    // use this instance to represent the endpoint of server
    server.sin_addr.s_addr = inet_addr("128.6.13.219");
    server.sin_family = AF_INET;
    //server.sin_port = htons(80);
    server.sin_port = htons(8888);

    //Connect to remote server

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    //keep communicating with server

    //printf("Enter message : ");
    //scanf("%s", message);

    // using http, for basic restful api: http://www.restapitutorial.com/lessons/httpmethods.html
    char *buffer = "GET / HTTP/1.0\r\n\r\n";

    //char *buffer = "test";
    //Send some data
    //send operation is not the function of c
    //if (send(sock, buffer, strlen(buffer), 0) < 0)
    int wSize = 0;
    wSize = write(sock, buffer, strlen(buffer));
    printf("return value of wSize %d\n", wSize);
    puts("message has been sent, prepare to get the respond from the server");

    if (wSize < 0)
    {
        puts("Send failed");
        return 1;
    }

    //Receive a reply from the server
    puts("Server reply :");
    char resp[10000];
    int len;

    // set the respond time limitation
    struct timeval tv;
    tv.tv_sec = 5;  /* 5 Secs Timeout */
    tv.tv_usec = 0; // Not init'ing this can cause strange errors
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv));

    while (1)
    {
        len = read(sock, resp, 9999);

        //printf("respond lenth %d\n",len);

        //if (len <= 0)
        //{
        //    break;
        //}

        // not a good way to recieve like this, it's better to use buffered io
        printf("%s\n", resp);
    }

    close(sock);
    return 0;
}
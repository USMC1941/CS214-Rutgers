#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h> //for gethostbyname
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define MAX_BUF 4096
#define SERVER_PORT 12138

struct user
{
    char name[32];
    char pwd[32];
};

int main(int argc, char *argv[])
{
    int sockfd; //socket
    char sendBuf[MAX_BUF], recvBuf[MAX_BUF];
    int sendSize, recvSize; //get the time right now
    struct hostent *host;
    struct sockaddr_in servAddr;
    char username[32];
    char password[32];
    int pid;
    struct user use;

    if (argc != 4)
    {
        perror("use: ./client [hostname] [username] [password]");
        exit(-1);
    }
    strcpy(use.name, argv[2]);
    strcpy(use.pwd, argv[3]);
    printf("username:%s\n", use.name);
    printf("password:%s\n", use.pwd);
    host = gethostbyname(argv[1]);
    if (host == NULL)
    {
        perror("fail to get host by name.");
        exit(-1);
    }
    printf("Success to get host by name ...\n");

    //construct a socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("fail to establish a socket");
        exit(1);
    }
    printf("Success to establish a socket...\n");

    /*init sockaddr_in*/
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(SERVER_PORT);
    servAddr.sin_addr = *((struct in_addr *)host->h_addr);
    //servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bzero(&(servAddr.sin_zero), 8);

    /*connect the socket*/
    if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr_in)) == -1)
    {
        perror("fail to connect the socket");
        exit(1);
    }
    printf("Success to connect the socket...\n");

    //send username and passwd to server
    if (send(sockfd, (char *)&use, sizeof(struct user), 0) == -1)
    {
        perror("fail to send datas.");
        exit(-1);
    }
    if ((recvSize = recv(sockfd, recvBuf, MAX_BUF, 0) == -1))
    {
        perror("fail to receive datas.");
        exit(-1);
    }
    //printf("Server:%s\n",recvBuf);
    if (strcmp(recvBuf, "no") == 0)
    {
        perror("wrong passwd");
        exit(-1);
    }

    //send-recv
    if ((pid = fork()) < 0)
    {
        perror("fork error\n");
    }
    else if (pid == 0) /*child*/
    {
        while (1)
        {
            fgets(sendBuf, MAX_BUF, stdin);
            printf("Me:%s\n", sendBuf);
            if (send(sockfd, sendBuf, strlen(sendBuf), 0) == -1)
            {
                perror("fail to receive datas.");
            }
            memset(sendBuf, 0, sizeof(sendBuf));
        }
    }
    else
    {
        while (1)
        {
            if ((recvSize = recv(sockfd, recvBuf, MAX_BUF, 0) == -1))
            {
                printf("Server maybe shutdown!");
                break;
            }
            printf("%s\n", recvBuf);
            memset(recvBuf, 0, sizeof(recvBuf));
        }
        kill(pid, SIGKILL);
    }

    close(sockfd);

    return 0;
}

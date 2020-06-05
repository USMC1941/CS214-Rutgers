#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define SERVER_PORT 12138
#define BACKLOG 20
#define MAX_CON_NO 10
#define MAX_DATA_SIZE 4096

struct user
{
    char name[32];
    char pwd[32];
};

int MAX(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

void print_time(char *ch, time_t *now)
{
    struct tm *stm;
    stm = localtime(now); //get the time right now
    sprintf(ch, "%02d:%02d:%02d\n", stm->tm_hour, stm->tm_min, stm->tm_sec);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in serverSockaddr, clientSockaddr;
    char sendBuf[MAX_DATA_SIZE], recvBuf[MAX_DATA_SIZE];
    int sendSize, recvSize;
    int sockfd, clientfd;
    fd_set servfd, recvfd;      //use for select()
    int fd_A[BACKLOG + 1];      //save the socket file descriptor of clients
    char fd_C[BACKLOG + 1][32]; //save the username of clients
    int conn_amount;            //count the number of clients
    int max_servfd, max_recvfd;
    int on = 1;
    socklen_t sinSize = 0;
    char username[32];
    char ch[64];
    int pid;
    int i, j;
    struct timeval timeout;
    struct user use;
    time_t now;
    struct tm *timenow;

    if (argc != 2)
    {
        printf("usage: ./server [username]\n");
        exit(1);
    }
    strcpy(username, argv[1]);
    printf("username:%s\n", username);

    /*establish a socket*/
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("fail to establish a socket");
        exit(1);
    }
    printf("Success to establish a socket...\n");

    /*init sockaddr_in*/
    serverSockaddr.sin_family = AF_INET;
    serverSockaddr.sin_port = htons(SERVER_PORT);
    serverSockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bzero(&(serverSockaddr.sin_zero), 8);

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    /*bind socket*/
    if (bind(sockfd, (struct sockaddr *)&serverSockaddr, sizeof(struct sockaddr)) == -1)
    {
        perror("fail to bind");
        exit(1);
    }
    printf("Success to bind the socket...\n");

    /*listen on the socket*/
    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("fail to listen");
        exit(1);
    }

    //time(&now);
    timeout.tv_sec = 2; //every 2 seconds
    timeout.tv_usec = 0;
    sinSize = sizeof(clientSockaddr); //to get IP and port

    FD_ZERO(&servfd); //clear all fds of server
    FD_ZERO(&recvfd); //clear all fds of client
    FD_SET(sockfd, &servfd);
    conn_amount = 0;
    max_servfd = sockfd;
    max_recvfd = 0;
    memset(fd_A, 0, sizeof(fd_A));
    memset(fd_C, 0, sizeof(fd_C));

    while (1)
    {
        FD_ZERO(&servfd); //clear all fds of server
        FD_ZERO(&recvfd); //clear all fds of client
        FD_SET(sockfd, &servfd);
        //timeout.tv_sec=30;//reduce the check frequency
        switch (select(max_servfd + 1, &servfd, NULL, NULL, &timeout))
        {
        case -1:
            perror("select error");
            break;
        case 0:
            break;
        default:
            //printf("has datas to offer accept\n");
            if (FD_ISSET(sockfd, &servfd)) //sockfd if have data, means can be accepted
            {
                /*accept a client's request*/
                if ((clientfd = accept(sockfd, (struct sockaddr *)&clientSockaddr, &sinSize)) == -1)
                {
                    perror("fail to accept");
                    exit(1);
                }
                printf("Success to accpet a connection request...\n");
                printf(">>>>>> %s:%d join in! ID(fd):%d \n", inet_ntoa(clientSockaddr.sin_addr), ntohs(clientSockaddr.sin_port), clientfd);
                //print_time(ch,&now);
                //time(&now);
                struct tm *info;
                time(&now);
                info = localtime(&now);
                printf("Join on:%s\n", asctime(info));

                if ((recvSize = recv(clientfd, (char *)&use, sizeof(struct user), 0)) == -1 || recvSize == 0)
                {
                    perror("fail to receive datas");
                }
                printf("Username from client:%s,Passwd:%s\n", use.name, use.pwd);
                memset(recvBuf, 0, sizeof(recvBuf));
                if (strcmp(use.pwd, "cs214") == 0)
                {
                    printf("Auth Success！\n");
                    strcpy(sendBuf, "yes");
                }
                else
                {
                    printf("Auth Failure！\n");
                    strcpy(sendBuf, "no");
                }
                if ((sendSize = send(clientfd, sendBuf, MAX_DATA_SIZE, 0)) == -1)
                {
                    perror("fail to receive datas");
                }
                //Write fd_set when a new client joins
                fd_A[conn_amount] = clientfd;
                strcpy(fd_C[conn_amount], use.name);
                conn_amount++;
                max_recvfd = MAX(max_recvfd, clientfd);
            }
            break;
        }
        //FD_COPY(recvfd,servfd);
        for (i = 0; i < MAX_CON_NO; i++)
        {
            if (fd_A[i] != 0)
            {
                FD_SET(fd_A[i], &recvfd);
            }
        }

        switch (select(max_recvfd + 1, &recvfd, NULL, NULL, &timeout))
        {
        case -1:
            //select error
            break;
        case 0:
            //timeout
            break;
        default:
            for (i = 0; i < conn_amount; i++)
            {
                if (FD_ISSET(fd_A[i], &recvfd))
                {
                    /*receive datas from client*/
                    if ((recvSize = recv(fd_A[i], recvBuf, MAX_DATA_SIZE, 0)) == -1 || recvSize == 0)
                    {
                        //perror("fail to receive datas");
                        //means the client is closed
                        printf("fd %d close\n", fd_A[i]);
                        FD_CLR(fd_A[i], &recvfd);
                        fd_A[i] = 0;
                    }
                    else //forward data from one client to other clients
                    {
                        /*send datas to client*/
                        strcpy(sendBuf, fd_C[i]);
                        strcat(sendBuf, " ");
                        time(&now);
                        print_time(ch, &now);
                        //Add a time stamp
                        strcat(sendBuf, ch);
                        strcat(sendBuf, "\t\t");
                        strcat(sendBuf, recvBuf);
                        printf("Data is:%s\n", sendBuf);
                        for (j = 0; j < MAX_CON_NO; j++)
                        {
                            if (fd_A[j] != 0 && i != j)
                            {
                                printf("Data send to %d,", fd_A[j]);
                                if ((sendSize = send(fd_A[j], sendBuf, strlen(sendBuf), 0)) != strlen(sendBuf))
                                {
                                    perror("fail");
                                    exit(1);
                                }
                                else
                                {
                                    printf("Success\n");
                                }
                            }
                        }
                        memset(recvBuf, 0, MAX_DATA_SIZE);
                    }
                }
            }
            break;
        }
    }
    return 0;
}

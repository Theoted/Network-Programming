#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

// Standard HTTP port
#define SERVER_PORT 80

#define MAXLINE 4096

#define SA struct sockaddr

void    err_n_die(const char *fmt) {
    write(2, fmt, strlen(fmt));
    exit(1);
}

int main(int argc, char **argv) {
    int                 sockfd, n;
    int                 sendbytes;
    struct  sockaddr_in serveraddr;
    char                sendline[MAXLINE];
    char                recvline[MAXLINE];

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_n_die("1");

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVER_PORT);
    
    if (inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) <= 0)
        err_n_die("2");

    if (connect(sockfd, (SA *) &serveraddr, sizeof(serveraddr)) < 0)
        err_n_die("3");

    sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
    sendbytes = strlen(sendline);

    if (write(sockfd, sendline, sendbytes) != sendbytes)
        err_n_die("4");

    memset(recvline, 0, MAXLINE);
    while ( (n = read(sockfd, recvline, MAXLINE - 1)) > 0)
    {
        printf("%s", recvline);
        memset(recvline, 0, MAXLINE);
    }

    return (0);
}

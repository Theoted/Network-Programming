#include "./common.h"

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

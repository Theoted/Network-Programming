#include "./common.h"

int main(int argc, char **argv)
{
    int listenfd, connfd, n;
    struct  sockaddr_in servaddr;
    uint8_t  buff[MAXLINE + 1];
    uint8_t  recvline[MAXLINE + 1];

    // Create a socket
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_n_die("1\n");

    // Set the server address
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERVER_PORT);

    // Bind serv setup and socket
    if ((bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
        err_n_die("2\n");
    
    if ((listen(listenfd, 10)) < 0)
        err_n_die("3\n");

    // Main loop
    for ( ; ; ) {
        struct sockaddr_in addr;
        socklen_t addr_len;

        fflush(stdout);
        connfd = accept(listenfd, (SA *) NULL, NULL);

        memset(recvline, 0, MAXLINE);

        // Read the client message
        while ((n = read(connfd, recvline, MAXLINE - 1)) > 0) {
            fprintf(stdout, "\n%s\n\n", recvline);
            
            if (recvline[n - 1] == '\n')
                break ;

            memset(recvline, 0, MAXLINE);
        }

        

        // Send response
        snprintf((char *)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\nBien le Web serv ?");
        write(connfd, (char *)buff, strlen((char *)buff));
        close(connfd);
    }

    return (0);
}
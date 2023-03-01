#ifndef COMMON_H
# define COMMON_H


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
#include <stdint.h>

// Standard HTTP port
#define SERVER_PORT 18000

#define MAXLINE 4096

#define SA struct sockaddr

void    err_n_die(const char *fmt);

#endif
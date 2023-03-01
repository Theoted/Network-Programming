NAME	= tcpserv
HEADER	= srcs/common.h


SRCS	=	srcs/common.c srcs/tcpserver.c 

OBJS	= ${SRCS:.c=.o}

CC		= gcc
# CFLAGS	= -Wall -Werror -Wextra #-fsanitize=address -g3

all: 	maker ${NAME}

%.o : %.c	${HEADER} Makefile
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS} 
		${CC} ${CFLAGS} ${OBJS}  -o $@ 
		
clean:
		rm -f ${OBJS}
	

fclean:	clean
		rm -f ${NAME}
		

re:		fclean all

.PHONY: all clean fclean re maker
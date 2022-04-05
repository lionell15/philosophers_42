NAME	=	philo
SRCS	=	philosophers.c \
			ft_atoi.c \
			start.c \
			utils.c

OBJS	=	${SRCS:.c=.o}
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g

.c.o:		%.o : %.c
			@gcc ${CFLAGS} -c $< -o $(<:.c=.o)

all: 		${NAME}

${NAME}:	${OBJS}
			@$(CC) ${CFLAGS}  ${OBJS} -o ${NAME}
clean:
			@rm -f ${OBJS}

fclean: 	clean
			@rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re
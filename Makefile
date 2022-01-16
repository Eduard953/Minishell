LIBFT=./libft

CC=gcc
CFLAGS=-Wall -Werror -Wextra
LDFLAGS=-L${LIBFT}

LDLIBS=-lft -lreadline
RM=rm -f

NAME=minishell

SRC=main.c
BONUS_SRC=

OBJ=${SRC:.c=.o}
BONUS_OBJ=${BONUS_SRC:.c=.o}

.PHONY: ${NAME} all clean fclean re libs

all: ${NAME}

${NAME}: libs
	${CC} ${CFLAGS} ${SRC} -o ${NAME} ${LDFLAGS} ${LDLIBS}

libs:
	make -C ${LIBFT} -j $(nproc) bonus

clean:
	make -C ${LIBFT} clean
	${RM} ${OBJ}
	${RM} ${BONUS_OBJ}

fclean: clean
	make -C ${LIBFT} fclean
	${RM} ${NAME}

re: fclean all

bonus: ${BONUS_OBJ}
	${CC} ${CFLAGS} ${OBJ} ${BONUS_OBJ} -o ${NAME} ${LDFLAGS} ${LDLIBS}

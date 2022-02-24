LIBFT=./libft

CC=gcc
CFLAGS=-Wall -Werror -Wextra -g
LDFLAGS=-L${LIBFT}

LDLIBS=-lft -lreadline
RM=rm -f

NAME=minishell

SRC=main.c execute_commands.c echo.c build_prompt.c cd.c create_instruction.c env.c exit.c export.c signal.c utils.c pwd.c error.c cwd.c find_token.c token_handlers.c launch_exe.c
BONUS_SRC=

OBJ=${SRC:.c=.o}
BONUS_OBJ=${BONUS_SRC:.c=.o}

.PHONY: ${NAME} all clean fclean re libs

all: ${NAME}

${NAME}: ${OBJ} libs
	${CC} ${CFLAGS} ${OBJ} -o ${NAME} ${LDFLAGS} ${LDLIBS}

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

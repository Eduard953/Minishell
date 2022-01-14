CC=gcc
CFLAGS=-Wall -Werror -Wextra
LDFLAGS=
LDLIBS=
AR=ar
ARFLAGS=rcsv
RM=rm -f

NAME=libft.a

SRC=ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c\
	ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c\
	ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c\
	ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c\
	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS_SRC=ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
		  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
		  ft_lstmap.c ft_lstadd_bonus.c ft_lstat_bonus.c ft_lstdelat_bonus.c\
		  ft_pow_bonus.c ft_sqrt_bonus.c ft_itobase_bonus.c ft_itohex_bonus.c\
		  ft_itobin_bonus.c ft_itooct_bonus.c ft_basetoi_bonus.c ft_hextoi_bonus.c\
		  ft_octtoi_bonus.c ft_bintoi_bonus.c ft_printc_bonus.c ft_print_bonus.c\
		  ft_printint_bonus.c ft_printintarr_bonus.c ft_printlst_bonus.c\
		  ft_printinthex_bonus.c ft_printintoct_bonus.c ft_printintbin_bonus.c\
		  ft_printintbase_bonus.c ft_println_bonus.c ft_printarr_bonus.c\
		  ft_isspace_bonus.c ft_isoneof_bonus.c ft_strext_bonus.c ft_max_bonus.c\
		  ft_min_bonus.c ft_abs_bonus.c ft_printuint_bonus.c ft_uitobase_bonus.c\
		  ft_strcmp_bonus.c

OBJ=${SRC:.c=.o}
BONUS_OBJ=${BONUS_SRC:.c=.o}

.PHONY: all clean fclean re

all: ${NAME}

${NAME}: libs ${OBJ}
	${AR} ${ARFLAGS} ${NAME} ${OBJ}

libs:

clean:
	${RM} ${OBJ}
	${RM} ${BONUS_OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

bonus: all ${BONUS_OBJ}
	${AR} ${ARFLAGS} ${NAME} ${BONUS_OBJ}

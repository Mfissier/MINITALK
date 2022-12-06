SRCS= ft_atoi.c     ft_isalpha.c  ft_memchr.c   ft_putchar_fd.c  ft_strdup.c    ft_strlen.c   ft_strtrim.c ft_bzero.c ft_memcmp.c   ft_putnbr_fd.c   ft_striteri.c  ft_strmapi.c  ft_substr.c ft_calloc.c   ft_isdigit.c  ft_memcpy.c   ft_putstr_fd.c   ft_strjoin.c   ft_strncmp.c  ft_tolower.c ft_isascii.c   ft_isprint.c  ft_memmove.c  ft_split.c       ft_strlcat.c   ft_strnstr.c  ft_toupper.c ft_isalnum.c  ft_itoa.c     ft_memset.c   ft_strchr.c      ft_strlcpy.c   ft_strrchr.c ft_putendl_fd.c ft_strstr.c
SRCBS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \

OBJS= ${SRCS:.c=.o}

BONUS = ${SRCBS:.c=.o}
NAME=libft.a
CC= gcc -g -Wall -Wextra -Werror

all: $(NAME)

bonus : $(BONUS)
	gcc -c $(SRCBS)
	ar rc $(NAME) $(BONUS)

$(NAME):$(OBJS)
	ar rc $(NAME) $(OBJS)

.c.o: $(SRCS)
	$(CC) $< -c -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)

.PHONY: all re clean fclean 

NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I. -c

SRC = ./ft_printf.c
SRC += ft_analysis_flag.c
SRC += ft_print_result.c
SRC += ft_putnbrbase.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	cp libft/libft.a .
	mv libft.a $(NAME)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	make clean -C libft
	rm -f $(OBJ) $(OBJB)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re

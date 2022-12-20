
LIBFT_PATH		=	./libs/libft
LIBFT			=	$(LIBFT_PATH)/libft.a

SOURCES_FILES	=	check_data_cmd.c 	\
					construct_list_1.c	\
					construct_list_2.c	\
					construct_list.c	\
					duplicate_list.c	\
					ft_built_in.c		\
					ft_clean_input.c	\
					ft_exec.c			\
					ft_exit.c			\
					ft_export_bis.c		\
					ft_export.c			\
					ft_free.c			\
					ft_init_env.c		\
					ft_parse.c			\
					list_1.c			\
					list_2.c			\
					list.c				\
					main.c				\
					multipipes.c		\
					utils_parse.c		\
					ft_redir.c			\
					ft_pipe.c			\
					ft_main_loop.c		\
					ft_manage_env.c		\

SOURCES_DIR		=	srcs

HEADER			=	$(SOURCES_DIR)/mini.h

SOURCES			=	$(addprefix $(SOURCES_DIR)/, $(SOURCES_FILES))

OBJECTS			= 	$(SOURCES:.c=.o)

NAME			=	minishell

CC				=	gcc
RM				=	rm -f

CFLAGS			=	-g -Wall -Werror -Wextra

LFLAGS			=	-L/usr/local/lib -I/usr/local/include -lreadline

.c.o:
				$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJECTS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)  $(LFLAGS)

$(LIBFT):
				$(MAKE) -C $(LIBFT_PATH)

clean:
				$(MAKE) -C $(LIBFT_PATH) clean
				$(RM) $(OBJECTS)

fclean:			clean
				$(MAKE) -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)

re:				fclean all

.SILENT:

.PHONY:			all clean fclean re libft

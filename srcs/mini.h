/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:14:43 by achretie          #+#    #+#             */
/*   Updated: 2022/12/06 14:11:44 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINI_H
# define MINI_H
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# define WRITE		1		
# define CMD		2
# define BUILTINS	3
# define ENV		4
# define GREAT		5
# define D_GREAT	6
# define LESS		7
# define D_LESS		8
# define NEW_PATH	9 
# define PIPE		10
# define CMD_OPT	11
# define FILE		12

# define C_RESET		"\x1B[0m"
# define C_BRIGHT 		"\x1B[1m"
# define C_DIM			"\x1B[2m"
# define C_UNDERLINE 	"\x1B[3m"
# define C_BLINK		"\x1B[5m"
# define C_REVERSE		"\x1B[7m"
# define C_HIDDEN		"\x1B[8m"

# define C_BLACK 		"\x1B[30m"
# define C_RED			"\x1B[31m"
# define C_GREEN		"\x1B[32m"
# define C_YELLOW		"\x1B[33m"
# define C_BLUE			"\x1B[34m"
# define C_MAGENTA		"\x1B[35m"
# define C_CYAN			"\x1B[36m"
# define C_WHITE		"\x1B[37m"


int	ret_v;
typedef struct s_pex
{
	int		nb_cmd;
	char	*cmd;
	int		**fd;
	char	**full_cmd;
	int		*pid;
	int		bug;
}				t_pex;

typedef struct s_env
{
	char			*content;
	char			*key;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_data
{
	char	*line;
	int		echo_flag;
	char	*echo_str;
	char	*cd_str;
	int		ret_value;
	int		exit;
	char	*cmd;
	char	**full_cmd;
	int		pid;
	int		idoc;
	t_env	*envp;
}				t_data;

typedef struct s_args
{
	char			*content_test;
	int				index_start;
	int				index_next;

	int				index;
	char			*content;
	char			*path;
	int				error;
	int				type;
	struct s_args	*next;
	struct s_args	*prev;
}				t_args;

//create_data_cmd.c
void	test_display_type(t_args **args, char *str);
int		identify_parse(char *sstr, char *flag, int value);
int		is_even_char(char *str, char c);
int		identify_parse_write(char *str);
int		identify_parse_cmd(char *cmd, char **envp, t_args **args);
void	fill_data_cmd(t_args **list, int *index, t_args **args, char **envp);
int		fill_list_args(t_args **args, char **sstr);
int		check_data_cmd(t_args **args, char **sstr, char **envp);
int		take_flag(int *start, int *end, t_args **list, char *flag);
int		take_parse_write(int *start, int *end, t_args **list);

//construct_list.c
char	 *cmd_clean(char *str);
int		construct_write(t_args **list, int *index, t_args **args);
int		construct_builtins_cmd(t_args **list, int *index);
int		construct_env(t_args **list, int *index, t_args **args);
int		construct_great(t_args **list, int *index, t_args **args);
int		construct_d_great(t_args **list, int *index, t_args **args);
int		construct_less(t_args **list, int *index, t_args **args);
int		construct_d_less(t_args **list, int *index, t_args **args);
int		construct_pipe(t_args **list, int *index, t_args **args);
int		construct_new_path(t_args **list, int *index, t_args **args);
int		construct_cmd_opt(t_args **list, int *index, t_args **args);

void	ft_echo(t_data *data);
void	ft_init_data(t_data *data, char **envp);
void	ft_pwd(void);

//list_2.c
int		ft_cd(t_data *data);
void	ft_echo(t_data *data);
void	ft_env(t_data *data);
void	ft_unset(t_data *data, char *var);
t_env	*ft_fill_list(t_env *head, char **envp, int envp_len);
int		ft_start_exec(t_data *data, char **envp, char *input);
char	*ft_parse_input(char *input);
char	*ft_parse_input_mini(char *input);
char	*ft_remove_space(char *input);
char	**ft_mini_split(char const *s, char c);
int		ft_verify_cmd(t_args *l_args, char	**new_tab, char **envp);
char	**ft_parse_path(char **envp);
int		ft_free_path(char **data);
void	ft_export(t_data *data, char *var);
t_env	*ft_lstadd_front_env(char *content, t_env *head);
char	*ft_get_key(char *content);
void	ft_add_to_env(t_data *data, char *arg);
void	ft_add_to_env_plus(t_data *data, char *arg);
void	ft_print_export(t_data *data);
int		multipipes(char **input, t_data *data, t_args *args);
char	*ft_execve_path(char **cmd, char **envp, t_pex *p);
void	ft_heredoc(t_data *data, char *delim);

//ft_parse
int		ft_free_path(char **data);
int		ft_start_exec(t_data *data, char **envp, char *input);
char	*ft_parse_input(char *input);
int    ft_try_access(char *cmd, char **envp);
char	*ft_parse_input_mini(char *input);
char    **ft_parse_path(char **envp);

//list_1.c
void	ft_indexage_list(t_args **list);
void	cpy_list(t_args **l_dst, t_args **l_src);
int		add_list_index(t_args **list, int i);
void	read_list(t_args **list);
void	ft_cd_list(t_args **tmp, t_args **source, int i);
void	cpy_create_list(t_args **l_dst, t_args **l_src);
int		create_and_duplicate_args(t_args **args, int idx, int check, char *cpy);
int		duplicate_list_with_start_beginning(t_args **args, char *cpy, int i, \
		int check);
int		handler_list(t_args **list, size_t start, size_t end, int *index);

//list.c
int		init_create_list(t_args **list);
int		add_last_list(t_args **list);
int		add_prev_list(t_args **list);
int		add_next_list(t_args **list);
int		add_start_list(t_args **list);
int		list_free(t_args **list);
void	ft_trap(int signal);

// ./utils_parse.c
int		analysis_operator(t_args **list, int *index, char **sstr, t_args **args);

// ./ft_free.c
void	free_sstr(char **sstr);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:17:36 by mafissie          #+#    #+#             */
/*   Updated: 2022/12/12 01:24:06 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

void	test_display_type(t_args **args, char *str)
{
	t_args		*tmp;
	static int	nbr;

	if (args == NULL)
	{
		printf("%s%sfun :[%s]\n%s", C_BLUE, C_REVERSE, str, C_RESET);
		return ;
	}
	printf("%s%sfun :[%s]\n%s", C_BLUE, C_REVERSE, str, C_RESET);
	tmp = *args;
	printf("%s%s%d/)[t_args *content]\n%s", C_BLUE, C_BLINK, nbr++, C_RESET);
	if (args == NULL)
		printf("%s%sfun :[%s] t_args *[NULL]\n%s", C_RED, C_REVERSE, str, \
				C_RESET);
	while (tmp->next != NULL)
	{
		if (tmp->type == WRITE)
			printf("%sindex [%d]: WRITE   \n%s", C_BRIGHT, tmp->index, C_RESET);
		if (tmp->type == CMD)
			printf("%sindex [%d]: CMD     \n%s", C_BRIGHT, tmp->index, C_RESET);
		if (tmp->type == BUILTINS)
			printf("%sindex [%d]: BUILTINS\n%s", C_BRIGHT, tmp->index, C_RESET);
		if (tmp->type == ENV)
			printf("%sindex [%d]: ENV     \n%s", C_BRIGHT, tmp->index, C_RESET);
		if (tmp->type == GREAT)
			printf("%sindex [%d]: GREAT   \n%s", C_BRIGHT, tmp->index, C_RESET);
		if (tmp->type == D_GREAT)
			printf("%sindex [%d]: D_GREAT \n%s", C_BRIGHT, tmp->index, C_RESET);
		if (tmp->type == LESS)
			printf("%sindex [%d]: LESS    \n%s", C_BRIGHT, tmp->index, C_RESET);
		if (tmp->type == D_LESS)
			printf("%sindex [%d]: D_LESS  \n%s", C_BRIGHT, tmp->index, C_RESET);
		if (tmp->type == NEW_PATH)
			printf("%sindex [%d]: NEW_PATH\n%s", C_BRIGHT, tmp->index, C_RESET);
		if (tmp->type == PIPE)
			printf("%sindex %d: PIPE\n%s", C_BRIGHT, tmp->index, C_RESET);
		if (tmp->type == CMD_OPT)
			printf("%sindex %d: CMD_OPT\n%s", C_BRIGHT, tmp->index, C_RESET);
		if (tmp->type == FILE)
			printf("%sindex %d: FILE\n%s", C_BRIGHT, tmp->index, C_RESET);			
		printf("%s%scontent [%d]: [%s]\n%s", C_GREEN, C_BRIGHT, \
			tmp->index, tmp->content, C_RESET);
		tmp = tmp->next;
	}
	if (tmp->type == WRITE)
		printf("%sindex [%d]: WRITE   \n%s", C_BRIGHT, tmp->index, C_RESET);
	if (tmp->type == CMD)
		printf("%sindex [%d]: CMD     \n%s", C_BRIGHT, tmp->index, C_RESET);
	if (tmp->type == BUILTINS)
		printf("%sindex [%d]: BUILTINS\n%s", C_BRIGHT, tmp->index, C_RESET);
	if (tmp->type == ENV)
		printf("%sindex [%d]: ENV     \n%s", C_BRIGHT, tmp->index, C_RESET);
	if (tmp->type == GREAT)
		printf("%sindex [%d]: GREAT   \n%s", C_BRIGHT, tmp->index, C_RESET);
	if (tmp->type == D_GREAT)
		printf("%sindex [%d]: D_GREAT \n%s", C_BRIGHT, tmp->index, C_RESET);
	if (tmp->type == LESS)
		printf("%sindex [%d]: LESS    \n%s", C_BRIGHT, tmp->index, C_RESET);
	if (tmp->type == D_LESS)
		printf("%sindex [%d]: D_LESS  \n%s", C_BRIGHT, tmp->index, C_RESET);
	if (tmp->type == NEW_PATH)
		printf("%sindex [%d]: NEW_PATH\n%s", C_BRIGHT, tmp->index, C_RESET);
	if (tmp->type == PIPE)
		printf("%sindex %d: PIPE\n%s", C_BRIGHT, tmp->index, C_RESET);
	if (tmp->type == CMD_OPT)
		printf("%sindex %d: CMD_OPT\n%s", C_BRIGHT, tmp->index, C_RESET);
	if (tmp->type == FILE)
		printf("%sindex %d: FILE\n%s", C_BRIGHT, tmp->index, C_RESET);
	printf("%s%scontent [%d]: [%s]\n%s", C_GREEN, C_BRIGHT, \
			tmp->index, tmp->content, C_RESET);
}

int	identify_parse(char *sstr, char *flag, int value)
{
	if (sstr == NULL)
		return (-1);
	if (flag != NULL && ft_strstr(sstr, flag))
		return (value);
	else if (ft_strstr(sstr, ".")
		|| ft_strstr(sstr, "./")
		|| ft_strstr(sstr, ".."))
		return (NEW_PATH);
	else if (ft_strstr(sstr, "$"))
		return (ENV);
	else
		return (WRITE);
}

int	is_even_char(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	if ((count == 0) || (count % 2 == 0))
		return (1);
	else
		return (0);
}

int	identify_parse_write(char *str)
{
	size_t	i;
	int		hook;
	int		start;

	hook = 0;
	start = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (str[i] == '"')
				hook = str[i];
			if (str[i] == '\'')
				hook = str[i];
			start = i;
			i++;
			while (str[i] && (str[i] != hook))
				i++;
			if (start == 0 && (i + 1) == ft_strlen(str))
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	identify_parse_cmd(char *cmd, char **envp, t_args **args)
{
	char	*new_cmd;
	int		check;

	new_cmd = NULL;
	if (access(cmd, F_OK) == 0) {
		return (1);
	}
	new_cmd = cmd_clean(cmd);
	if (new_cmd == NULL)
		return (0);
	check = ft_try_access(new_cmd, envp);
	if (check)
	{
		free(new_cmd);
		return (1);
	}
	else if (check == -1)
	{
		list_free(args);
		exit (2);
	}
	free(new_cmd);
	return (0);
}

void	fill_data_cmd(t_args **list, int *index, t_args **args, char **envp)
{
	int check;

	check = 0;
	ft_cd_list(list, args, *index);

	if (identify_parse_cmd((*list)->content, envp, args) == 1)
	{
		check = construct_builtins_cmd(list, index);
		if (check == -1)
			return ;
	}
	else if (construct_d_less(list, index, args) == 1)
		return ;
	else if (construct_d_great(list, index, args) == 1)
		return ;
	else if (construct_great(list, index, args) == 1)
		return ;
	else if (construct_less(list, index, args) == 1)
		return ;
	else if (construct_pipe(list, index, args) == 1)
		return ;
	else if (construct_new_path(list, index, args) == 1)
		return ;
	else if (construct_env(list, index, args) == 1)
		return ;
	else
		(*list)->type = WRITE;
	*index += 1;
}

int	fill_list_args(t_args **args, char **sstr)
{
	int		i;
	t_args	*tmp;

	i = 0;
	tmp = NULL;
	tmp = *args;
	tmp->content = NULL;
	tmp->content = ft_strdup(sstr[i]);
	if (tmp->content == NULL)
		return (-1);
	while (sstr[++i] != NULL)
	{
		add_start_list(args);
		ft_cd_list(&tmp, args, i);
		tmp->content = NULL;
		tmp->content = ft_strdup(sstr[i]);
		if (tmp->content == NULL)
			return (-1);
	}
	ft_indexage_list(args);
	return (0);
}

int	is_end_parsing(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp->next != NULL)
	{
		if (tmp->type <= 0)
			return (1);
		tmp = tmp->next;
	}
	if (tmp->type <= 0)
		return (1);
	else
		return (0);
}

void	fill_last_param(t_args **tmp, t_args **args, char **envp)
{
	int		i;
	char	*new_cmd_next;
	char	*new_cmd;
	int		fd;
	int 	check;

	check = 0;
	(void)envp;
	(void)fd;
	new_cmd_next = NULL;
	new_cmd = NULL;
	i = 0;
	ft_cd_list(tmp, args, i);
	if ((*tmp)->type == WRITE)
		(*tmp)->type = CMD;
	while (1)
	{
		if ((*tmp)->next != NULL)
			new_cmd_next = cmd_clean((*tmp)->next->content);
		new_cmd = cmd_clean((*tmp)->content);
		if ((*tmp)->type == WRITE)
		{
			if (ft_strlen(new_cmd) == 2)
			{
				if (new_cmd[0] == 'c' && new_cmd[1] == 'd')
				{
					(*tmp)->type = CMD;
					i = 0;
					ft_cd_list(tmp, args, i);
					continue;
				}
			}
		}
		if ((*tmp)->type == CMD || (*tmp)->type == BUILTINS)
		{
			if (new_cmd_next != NULL && new_cmd_next[0] == '-')
				(*tmp)->next->type = CMD_OPT;
			if ((*tmp)->next != NULL && strstr(new_cmd, "echo"))
				(*tmp)->next->type = WRITE;
			else if ((*tmp)->next != NULL && strstr(new_cmd, "ls") && (*tmp)->next->type != CMD_OPT)
				(*tmp)->next->type = WRITE;	
		}
		if ((*tmp)->type == D_GREAT || (*tmp)->type == GREAT || (*tmp)->type == LESS)
		{
			if ((*tmp)->next != NULL)
				(*tmp)->next->type = FILE;
		}
		if ((*tmp)->type == PIPE)
		{
			if ((*tmp)->next != NULL)
				if ((*tmp)->next->type == WRITE)
					(*tmp)->next->type = CMD;
		}
		free(new_cmd_next);
		free(new_cmd);
		new_cmd = NULL;
		new_cmd_next = NULL;
		if (check == 1)
			break ;
		ft_cd_list(tmp, args, i);
		if ((*tmp)->next == NULL)
			check = 1;
		i++;
	}
}


int	check_data_cmd(t_args **args, char **sstr, char **envp)
{
	t_args	*tmp;
	int		i;

	i = 0;
	if (fill_list_args(args, sstr))
	{
		list_free(args);
		free_sstr(sstr);
		exit (2);
	}
	free_sstr(sstr);
	tmp = *args;
	while (is_end_parsing(args))
	{
		fill_data_cmd(&tmp, &i, args, envp);
		if (tmp->next == NULL)
		{
			fill_data_cmd(&tmp, &i, args, envp);
			if (!is_end_parsing(args))
				break ;
			i = 0;
		}
	}
	fill_last_param(&tmp, args, envp);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2022/12/05 15:03:35 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_heredoc(t_data *data, char *delim)
{
	char	*input;
	char	*stock;

	stock = ft_calloc(sizeof(char), 1);
	while (1)
	{
		data->idoc++;
		input = readline("> ");
		if (!input)
		{
			printf("Minishell: warning: here-document at line %d delimited by end-of-file (wanted \'%s\')\n", data->idoc, delim);
			break ;
		}
		if (!ft_strncmp(input, delim, ft_strlen(delim)))
			break ;
		stock = ft_strjoin(stock, input);
		stock = ft_strjoin(stock, "\n");
	}
}

void	ft_redir_less(t_pex *p, t_args *args)
{
	int		file;

	(void)p;
	if (args->next)
	{
		if (access(args->next->content, F_OK) != 0)
		{
			printf("Minishell: %s: No such file or directory", args->next->content);
			ret_v = 1;
			return ;
		}
	}
	else
	{
		printf("Minishell: syntax error near unexpected token \'newline\'\n");
		ret_v = 2;
	}
	file = open(args->next->content, O_RDONLY, 0777);
	dup2(file, STDIN_FILENO);
	close(file);
}

void	ft_redir_db_less(t_pex *p, t_data *data, t_args *args)
{
	char	*delim;

	(void)p;
	if (!args->next)
		return ;
	delim = args->next->content;
	ft_heredoc(data, delim);
}

void	ft_redir_great(t_pex *p, t_args *args)
{
	int		file;

	(void)p;
	if (args->next)
	{
		if (access(args->next->content, F_OK) != 0)
		{
			printf("Minishell: %s: No such file or directory", args->next->content);
			ret_v = 1;
			return ;
		}
	}
	else
	{
		printf("Minishell: syntax error near unexpected token \'newline\'\n");
		ret_v = 2;
	}
	file = open(args->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(file, STDOUT_FILENO);
	close(file);
}

void	ft_redir_db_great(t_pex *p, t_args *args)
{
	int		file;

	(void)p;
	if (args->next)
	{
		if (access(args->next->content, F_OK) != 0)
		{
			printf("Minishell: %s: No such file or directory", args->next->content);
			ret_v = 1;
			return ;
		}
	}
	else
	{
		printf("Minishell: syntax error near unexpected token \'newline\'\n");
		ret_v = 2;
	}
	file = open(args->next->content, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0777);
	dup2(file, STDOUT_FILENO);
	close(file);
}

void	ft_redir_parse(t_pex *p, t_data *data, t_args *args)
{
	if (args->type == D_LESS)
		ft_redir_db_less(p, data, args);
	else if (args->type == LESS)
		ft_redir_less(p, args);
	else if (args->type == D_GREAT)
		ft_redir_db_great(p, args);
	else if (args->type == GREAT)
		ft_redir_great(p, args);
	
}

void	ft_end_pipes(t_pex *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmd)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		waitpid(p->pid[i], NULL, 0);
		i++;
	}
}

char	**ft_env_to_tab(t_data *data)
{
	t_env   *tmp;
    int     i;
    char    **envp;

    i = 0;
	tmp = data->envp;
	while (data->envp)
	{
		i++;
		data->envp = data->envp->next;
	}
	data->envp = tmp;
    envp = malloc(sizeof(char *) * i + 1);
    i = 0;
    while (data->envp)
	{
		envp[i] = ft_strdup(data->envp->content);
		data->envp = data->envp->next;
        i++;
	}
    data->envp = tmp;
    envp[i] = NULL;
    return (envp);
}

int ft_get_nb_cmd(char **input, t_pex *p)
{
    int i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
    	i++;
	p->fd = ft_calloc(sizeof(char *), i + 1);
	while (j < i)
		p->fd[j++] = ft_calloc(sizeof(char), 3);
	p->pid = ft_calloc(sizeof(int), i + 1);
    return (i);
}

void	ft_case_first(t_pex *p, char **envp, int i)
{
	dup2(p->fd[i][1], STDOUT_FILENO);
	close(p->fd[i][0]);
	close(p->fd[i][1]);
	execve(p->cmd, p->full_cmd, envp);
}

void	ft_case_mid(t_pex *p, char **envp, int i)
{
	dup2(p->fd[i - 1][0], STDIN_FILENO);
	dup2(p->fd[i][1], STDOUT_FILENO);
	close(p->fd[i][0]);
	close(p->fd[i][1]);
	execve(p->cmd, p->full_cmd, envp);
}

void	ft_case_last(t_pex *p, char **envp, int i)
{
	dup2(p->fd[i - 1][0], STDIN_FILENO);
	close(p->fd[i][0]);
	close(p->fd[i][1]);
	execve(p->cmd, p->full_cmd, envp);
}

int	ft_exec_cmd(t_pex *p, int i, char **envp)
{
	pipe(p->fd[i]);
	p->pid[i] = fork();
	if (p->pid[i] < 0)
		return (-1);
	if (p->pid[i] == 0)
	{
		if (i == 0)
			ft_case_first(p, envp, i);
		else if (i < p->nb_cmd - 1)
			ft_case_mid(p, envp, i);
		else
			ft_case_last(p, envp, i);
	}
	else
	{
		if (i == 0)
			close(p->fd[i][1]);
		else if (i < p->nb_cmd)
		{
			close(p->fd[i - 1][0]);
			close(p->fd[i][1]);
		}
		else
			close(p->fd[i - 1][0]);
	}
	return (0);
}

void    ft_init_pex(t_pex *p, char **input, t_data *data, t_args *args)
{
    int i;
    char    **envp;

	(void)args;
    envp = ft_env_to_tab(data);
    i = 0;
    p->nb_cmd = ft_get_nb_cmd(input, p);
    p->bug = 0;
    while (i < p->nb_cmd)
    {	
	    p->full_cmd = ft_split(input[i], ' ');
        p->cmd = ft_execve_path(p->full_cmd, envp, p);
		//ft_redir_parse(p, data, args);
		ft_exec_cmd(p, i, envp);
		ft_free_path(p->full_cmd);
		free(p->cmd);
        i++;
    }
}

int	multipipes(char **input, t_data *data, t_args *args)
{
	t_pex	p;

    ft_init_pex(&p, input, data, args);
	ft_end_pipes(&p);
	return (0);
}

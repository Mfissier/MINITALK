/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2022/12/20 09:32:04 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int ft_get_nb_cmd(t_args *args, t_pex *p)
{
    int i;
	int	j;
	t_args *tmp;

	tmp = args;
	i = 1;
	j = 0;
	while (args->next)
	{
		if (!ft_strncmp(args->content, "|", ft_strlen(args->content)))
			i++;
		args = args->next;
	}
	args = tmp;
	p->fd = ft_calloc(sizeof(char *), i + 1);
	while (j < i)
		p->fd[j++] = ft_calloc(sizeof(char), 3);
	p->pid = ft_calloc(sizeof(int), i + 1);
    return (i);
}

int	ft_isbuiltin(t_args *args, t_data *data)
{
	if (!ft_strncmp(args->content, "cd", ft_strlen(args->content)))
	{
		if (args->next)
		{
			if (args->next->next)
			{
				printf("Minishell: cd: too many arguments\n");
				return (1);
			}
			data->cd_str = ft_strdup(args->next->content);
		}
		ft_cd(data);
		return (1);
	}
	if (!ft_strncmp(args->content, "echo", ft_strlen(args->content)))
	{
		ft_echo(args);
		return (1);
	}
	if (!ft_strncmp(args->content, "pwd", ft_strlen(args->content)))
	{
		ft_pwd();
		return (1);
	}
	if (!ft_strncmp(args->content, "env", ft_strlen(args->content)))
	{
		ft_env(data);
		return (1);
	}
	if (!ft_strncmp(args->content, "unset", ft_strlen(args->content)))
	{
		ft_unset(data, args->content);
		return (1);
	}
	if (!ft_strncmp(args->content, "exit", ft_strlen(args->content)))
		ft_exit(args, data);
	return (0);
}

void	ft_exec_cmd(t_pex *p, char **envp, t_data *data)
{
	int		status = 0;

	p->solo_pid = fork();
	if (p->solo_pid == -1)
		perror("fork");
	else if (p->solo_pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(p->solo_pid, &status, 0);
		if (status == 2)
			printf("\n");
		if (status == 131)
			printf("Quit (core dumped)\n");
		kill(p->solo_pid, SIGTERM);
	}
	else 
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (data->out != -1)
		{
			dup2(data->out, STDOUT_FILENO);
			close(data->out);
		}
		if (data->in != -1)
		{
			dup2(data->in, STDIN_FILENO);
			close(data->in);
		}
		if (execve(p->cmd, p->full_cmd, envp) == -1)
			printf("%s: command not found\n", p->full_cmd[0]);
		exit (0);
	}
}

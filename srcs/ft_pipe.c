/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2022/12/20 08:59:16 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_end_pipes(t_pex *p)
{
	int	i;

	i = 1;
	while (i < p->nb_cmd)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		waitpid(p->pid[i], NULL, 0);
		i++;
	}
}

int	ft_exec_pipe(t_pex *p, int i, char **envp, t_data *data)
{
	int status;

	status = 0;
	pipe(p->fd[i]);
	p->pid[i] = fork();
	if (p->pid[i] < 0)
		return (-1);
	if (p->pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (i == 0)
			ft_case_first(p, envp, i, data);
		else if (i < p->nb_cmd - 1)
			ft_case_mid(p, envp, i, data);
		else
			ft_case_last(p, envp, i, data);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(p->pid[i], &status, 0);
		if (status == 2)
			printf("\n");
		if (status == 131)
			printf("Quit (core dumped)\n");
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

void	ft_case_first(t_pex *p, char **envp, int i, t_data *data)
{
	if (data->in != -1)
	{
		dup2(data->in, STDIN_FILENO);
		close(data->in);
	}
	dup2(p->fd[i][1], STDOUT_FILENO);
	if (data->out != -1)
	{
		dup2(data->out, STDOUT_FILENO);
		close(data->out);
	}
	close(p->fd[i][0]);
	close(p->fd[i][1]);
	execve(p->cmd, p->full_cmd, envp);
}

void	ft_case_mid(t_pex *p, char **envp, int i, t_data *data)
{
	dup2(p->fd[i - 1][0], STDIN_FILENO);
	dup2(p->fd[i][1], STDOUT_FILENO);
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
	close(p->fd[i][0]);
	close(p->fd[i][1]);
	execve(p->cmd, p->full_cmd, envp);
}

void	ft_case_last(t_pex *p, char **envp, int i, t_data *data)
{
	dup2(p->fd[i - 1][0], STDIN_FILENO);
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
	close(p->fd[i][0]);
	close(p->fd[i][1]);
	execve(p->cmd, p->full_cmd, envp);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:45:23 by achretie          #+#    #+#             */
/*   Updated: 2022/11/30 19:08:49 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_args(char **av)
{
	if (access(av[1], F_OK) != 0)
	{
		write(2, "Error with files !\n", 19);
		exit (0);
	}
	return (0);
}

void	ft_child_one(t_data *p, int file1, char **envp)
{
	dup2(file1, STDIN_FILENO);
	dup2(p->fd[1], STDOUT_FILENO);
	close(p->fd[0]);
	close(p->fd[1]);
	close(file1);
	execve(p->cmd1, p->full_cmd1, envp);
}

void	ft_child_two(t_data *p, int file2, char **envp)
{
	dup2(p->fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close(p->fd[0]);
	close(p->fd[1]);
	close(file2);
	execve(p->cmd2, p->full_cmd2, envp);
}

int	pipex(char **envp, t_data *p, char **av)
{
	int		file1;
	int		file2;

	file1 = open(av[1], O_RDONLY, 0777);
	file2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipe(p->fd) == -1)
		return (-1);
	p->pid1 = fork();
	if (p->pid1 < 0)
		return (-1);
	if (p->pid1 == 0)
		ft_child_one(p, file1, envp);
	p->pid2 = fork();
	if (p->pid2 < 0)
		return (-1);
	if (p->pid2 == 0)
		ft_child_two(p, file2, envp);
	ft_end(p, file1, file2);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	p;

	if (ac != 5)
	{
		write(2, "Wrong arguments !\n", 18);
		return (0);
	}
	ft_check_args(av);
	p.bug = 0;
	p.full_cmd1 = ft_split(av[2], ' ');
	p.full_cmd2 = ft_split(av[3], ' ');
	p.cmd1 = ft_execve_path(p.full_cmd1, envp, &p);
	if (!p.bug)
		p.cmd2 = ft_execve_path(p.full_cmd2, envp, &p);
	if (!p.bug)
		pipex(envp, &p, av);
	else
	{
		write(2, "Error with command\n", 20);
		free(p.cmd1);
	}
	ft_free_data(p.full_cmd1);
	ft_free_data(p.full_cmd2);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:14:43 by achretie          #+#    #+#             */
/*   Updated: 2022/06/07 21:09:29 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libs/ft_printf/ft_printf.h"

typedef struct s_data
{
	char	*cmd1;
	char	*cmd2;
	int		fd[2];
	char	**full_cmd1;
	char	**full_cmd2;
	int		pid1;
	int		pid2;
	int		bug;
}				t_data;

char	**ft_split(char const *s, char c);
char	**ft_parse_path(char **envp);
char	*ft_execve_path(char **cmd, char **envp, t_data *p);
int		ft_free_data(char **data);
void	ft_end(t_data *p, int file1, int file2);
#endif

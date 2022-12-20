/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2022/12/20 08:55:32 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_redir_less(char **split, int i, t_data *data)
{
	if (split[i + 1])
	{
		if (!ft_strcmp(split[i + 1], "&") || !ft_strcmp(split[i + 1], "|") || \
			!ft_strcmp(split[i + 1], "<") || !ft_strcmp(split[i + 1], ">") || \
			!ft_strcmp(split[i + 1], ";") || !ft_strcmp(split[i + 1], "(") || \
			!ft_strcmp(split[i + 1], ")"))
		{
			printf("bash: syntax error near unexpected token `%s'\n", split[i + 1]);
			data->bug = 1;
		}
		else if (access(split[i + 1], F_OK) != 0)
		{
			printf("Minishell: %s: No such file or directory\n", split[i + 1]);
			ret_val = 1;
			data->bug = 1;
			return ;
		}
		else
			data->in = open(split[i + 1], O_RDONLY, 0644);
	}
	else
	{
		printf("Minishell: syntax error near unexpected token \'newline\'\n");
		data->bug = 1;
		ret_val = 2;
	}
}

void	ft_redir_db_less(char **split, int i, t_data *data)
{
	char	*delim;

	if (!split[i + 1])
	{
		printf("Minishell: syntax error near unexpected token \'newline\'\n");
		data->bug = 1;
		return ;
	}
	delim = split[i + 1];
	ft_heredoc(data, delim);
}

void	ft_redir_great(char **split, int i, t_data *data)
{
	if (split[i + 1])
	{
		if (!ft_strcmp(split[i + 1], "&") || !ft_strcmp(split[i + 1], "|") || \
			!ft_strcmp(split[i + 1], "<") || !ft_strcmp(split[i + 1], ">") || \
			!ft_strcmp(split[i + 1], ";") || !ft_strcmp(split[i + 1], "(") || \
			!ft_strcmp(split[i + 1], ")"))
		{
			printf("bash: syntax error near unexpected token `%s'\n", split[i + 1]);
			data->bug = 1;
		}
		else
			data->out = open(split[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		printf("%s", "Minishell: syntax error near unexpected token \'newline\'\n");
		data->bug = 1;
		ret_val = 2;
	}
}

void	ft_redir_db_great(char **split, int i, t_data *data)
{
	if (split[i + 1])
	{
		if (!ft_strcmp(split[i + 1], "&") || !ft_strcmp(split[i + 1], "|") || \
			!ft_strcmp(split[i + 1], "<") || !ft_strcmp(split[i + 1], ">") || \
			!ft_strcmp(split[i + 1], ";") || !ft_strcmp(split[i + 1], "(") || \
			!ft_strcmp(split[i + 1], ")"))
		{
			printf("bash: syntax error near unexpected token `%s'\n", split[i + 1]);
			data->bug = 1;
		}
		else
			data->out = open(split[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		printf("%s", "Minishell: syntax error near unexpected token \'newline\'\n");
		data->bug = 1;
		ret_val = 2;
	}
}

char	*ft_redir_parse(t_data *data, char *str)
{
	char	**split;
	char	*clean;
	int		i;
	int		j;

	clean = ft_calloc(sizeof(char), 1);
	j = 0;
	i = 0;
	split = ft_split(str, ' ');
	while (split[i])
	{
		if (!ft_strcmp(split[i], "<<"))
		{
			ft_redir_db_less(split, i, data);
			j++;
			i++;
		}
		else if (!ft_strcmp(split[i], "<"))
		{
			ft_redir_less(split, i, data);
			j++;
			i++;
		}
		else if (!ft_strcmp(split[i], ">>"))
		{
			ft_redir_db_great(split, i, data);
			j++;
			i++;
		}
		else if (!ft_strcmp(split[i], ">"))
		{
			ft_redir_great(split, i, data);
			j++;
			i++;
		}
		else
		{
			if (!j)
				clean = ft_strjoin(clean, split[i]);
			else
				j = 0;
			if (split[i + 1])
				clean = ft_strjoin(clean, " ");
			i++;
		}
		if (data->bug)
			break ;
	}
	ft_free_path(split);
	return (clean);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:24:10 by achretie          #+#    #+#             */
/*   Updated: 2022/08/22 15:24:20 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	ft_free_data(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	max_len;
	char	*str;
	int		i;
	int		j;

	max_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * max_len);
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i++] = s2[j];
	str[i] = 0;
	return (str);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	x;
	size_t	j;

	i = -1;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[++i] && i < len)
	{
		if (str[i] == to_find[0])
		{
			j = i - 1;
			x = -1;
			while (str[++j] == to_find[++x] && j < len)
				if (to_find[x + 1] == '\0')
					return ((char *)str + i);
		}
	}
	return (0);
}

char	**ft_parse_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	path = ft_split(envp[i] + 5, ':');
	return (path);
}

char	*ft_execve_path(char **cmd, char **envp, t_data *p)
{
	char	**path;
	char	*word;
	char	*full_word;
	int		i;

	if (ft_strnstr(cmd[0], "/", ft_strlen(cmd[0])))
		return (cmd[0]);
	path = ft_parse_path(envp);
	i = -1;
	while (path[++i])
	{
		word = ft_strjoin(path[i], "/");
		full_word = ft_strjoin(word, cmd[0]);
		if (access(full_word, F_OK) == 0)
		{
			free(word);
			ft_free_data(path);
			return (full_word);
		}
		free(word);
		free(full_word);
	}
	p->bug = 1;
	ft_free_data(path);
	return (0);
}

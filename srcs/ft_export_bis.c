/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:13:23 by achretie          #+#    #+#             */
/*   Updated: 2022/11/19 20:26:53 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_print_tabl(char **tabl)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (tabl[i])
	{
		if (tabl[i][0] == '_' && tabl[i][1] == '=')
		{
			i++;
			continue ;
		}
		printf("declare -x ");
		while (tabl[i][j] != '=' && tabl[i][j])
		{
			printf("%c", tabl[i][j]);
			j++;
		}
		if (tabl[i][j])
		{
			printf("=\"");
			j++;
		}
		while (tabl[i][j])
		{
			printf("%c", tabl[i][j]);
			j++;
		}
		i++;
		j = 0;
		printf("\"\n");
	}
	ft_free_path(tabl);
}

void	ft_print_export_bis(char **tabl)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 1;
	while (tabl[j])
	{
		while (tabl[i])
		{
			if (ft_strcmp(tabl[i], tabl[j]) > 0)
			{
				tmp = tabl[i];
				tabl[i] = tabl[j];
				tabl[j] = tmp;
			}
			i++;
		}
		i = 0;
		j++;
	}
	ft_print_tabl(tabl);
}

void	ft_print_export(t_data *data)
{
	t_env	*save;
	char	**tabl;
	int		i;

	i = 0;
	save = data->envp;
	while (data->envp->next)
	{
		i++;
		data->envp = data->envp->next;
	}
	data->envp = save;
	tabl = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (data->envp->next)
	{
		tabl[i] = ft_strdup(data->envp->content);
		data->envp = data->envp->next;
		i++;
	}
	data->envp = save;
	ft_print_export_bis(tabl);
}

void	ft_add_to_env_plus(t_data *data, char *arg)
{
	t_env	*save;
	char	*key;

	key = ft_get_key(arg);
	save = data->envp;
	while (data->envp->next)
	{
		if (ft_strncmp(data->envp->key, key, ft_strlen(key)) == 0 && ft_strlen(key) == ft_strlen(data->envp->key))
		{
			if (ft_strlen(data->envp->content) != ft_strlen(data->envp->key))
			{
				data->envp->content = ft_strjoin(data->envp->content, arg + ft_strlen(key) + 2);
				data->envp = save;
				free(key);
				return ;
			}
			else
			{
				data->envp->content = ft_strjoin(data->envp->content, "=");
				data->envp->content = ft_strjoin(data->envp->content, arg + ft_strlen(key) + 2);
				data->envp = save;
				free(key);
				return ;
			}

		}
		data->envp = data->envp->next;
	}
	data->envp = save;
	data->envp = ft_lstadd_front_env(key, data->envp);
	free(key);
}

void	ft_add_to_env(t_data *data, char *arg)
{
	t_env	*save;
	char	*key;

	key = ft_get_key(arg);
	save = data->envp;
	while (data->envp->next)
	{
		if (ft_strncmp(data->envp->key, key, ft_strlen(key)) == 0 && ft_strlen(key) == ft_strlen(data->envp->key))
		{
			free(data->envp->content);
			data->envp->content = ft_strdup(arg);
			data->envp = save;
			free(key);
			return ;
		}
		data->envp = data->envp->next;
	}
	data->envp = save;
	free(key);
}

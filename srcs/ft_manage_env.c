/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:13:52 by achretie          #+#    #+#             */
/*   Updated: 2022/12/20 09:18:52 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_setenv(t_data *data, char *var, char *content) //Permet de modifier une variable de notre env
{
	t_env	*save;

	save = data->envp;
	while (data->envp->next)
	{
		if (ft_strncmp(data->envp->content, var, ft_strlen(var)) == 0 && ft_strlen(var) == ft_strlen(data->envp->key))
		{
			free(data->envp->content);
			data->envp->content = ft_strdup(var);
			data->envp->content = ft_strjoin(data->envp->content, "=");
			data->envp->content = ft_strjoin(data->envp->content, content);
			data->envp = save;
			return (1);
		}
		data->envp = data->envp->next;
	}
	data->envp = save;
	return (0);
}

char	*ft_getenv(t_data *data, char *var) //Permet de recuperer la valeur d'une variable de notre env
{
	t_env	*save;
	char	*content;

	save = data->envp;
	while (data->envp->next)
	{
		if (ft_strncmp(data->envp->content, var, ft_strlen(var)) == 0 && ft_strlen(var) == ft_strlen(data->envp->key))
		{
			content = ft_strdup(data->envp->content + ft_strlen(var) + 1);
			data->envp = save;
			return (content);
		}
		data->envp = data->envp->next;
	}
	data->envp = save;
	return (NULL);
}

void	ft_env(t_data *data)
{
	t_env *tmp;

	tmp = data->envp;
	while (data->envp)
	{
		printf("%s\n", data->envp->content);
		data->envp = data->envp->next;
	}
	data->envp = tmp;
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
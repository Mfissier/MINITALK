/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:13:52 by achretie          #+#    #+#             */
/*   Updated: 2022/12/06 14:07:04 by mafissie         ###   ########.fr       */
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

void	ft_unset(t_data *data, char *var)
{
	t_env	*save;
	t_env	*tmp;

	save = data->envp;
	if (ft_strncmp(data->envp->content, var, ft_strlen(var)) == 0 && ft_strlen(var) == ft_strlen(data->envp->key))
	{
		tmp = data->envp;
		data->envp = data->envp->next;
		free(tmp);
		return ;
	}
	while (data->envp->next)
	{
		if (ft_strncmp(data->envp->next->content, var, ft_strlen(var)) == 0 && ft_strlen(var) == ft_strlen(data->envp->next->key))
		{
			tmp = data->envp->next;
			data->envp->next = tmp->next;
			free(tmp);
			break ;
		}
		data->envp = data->envp->next;
	}
	data->envp = save;
}

void	ft_init_data(t_data *data, char **envp)
{
	int		i;
	t_env	*head;

	head = NULL;
	i = 0;
	while (envp[i])
		i++;
	head = ft_fill_list(head, envp, i);
	data->envp = head;
}

void	ft_echo(t_data *data)
{
	if (!data->echo_flag)
		printf("%s\n", data->echo_str);
	else if (data->echo_flag)
		printf("%s", data->echo_str);
}

void	ft_pwd(void)
{
	char	buffer[10000];

	getcwd(buffer, 10000);
	printf("%s\n", buffer);
}

int	ft_cd(t_data *data) //Penser a verifier si les $var sont accessibles et on pas etait unset ?
{
	char	str[10000];
	char	*stock;
	char	*old_pwd;

	old_pwd = ft_getenv(data, "PWD");
	if (!data->cd_str) //cd sans argument, renvoie a HOME
	{
		stock = ft_getenv(data, "HOME");
		if (chdir(stock) == -1)
		{
			free(stock);
			return (-1);
		}
		ft_setenv(data, "PWD", stock);
	}
	else
	{
		if (chdir(data->cd_str) == -1)
		{
			free(old_pwd);
			return (-1);
		}
		getcwd(str, 10000);
		ft_setenv(data, "PWD", str);
	}
	ft_setenv(data, "OLDPWD", old_pwd);
	return (0);
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

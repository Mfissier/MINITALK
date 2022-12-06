/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:06:00 by achretie          #+#    #+#             */
/*   Updated: 2022/11/19 20:10:05 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_find_key(t_data *data, char *arg)
{
	t_env	*save;
	char	*key;

	key = ft_get_key(arg);
	save = data->envp;
	while (data->envp->next)
	{
		if (ft_strncmp(data->envp->key, key, ft_strlen(key)) == 0 && ft_strlen(key) == ft_strlen(data->envp->key))
		{
			data->envp = save;
			free(key);
			return (1);
		}
		data->envp = data->envp->next;
	}
	data->envp = save;
	free(key);
	return (0);
}

int	ft_check_export_key(char *arg, int i)
{
	int	j;

	j = 1;
	while (j < i)
	{
		if ((arg[j] < 'A' || arg[j] > 'Z') && (arg[j] < 'a' || arg[j] > 'z') && (arg[j] < '0' || arg[j] > '9') && arg[j] != '+')
			return (1);
		if (arg[j] == '+')
		{
			if (j + 1 != i)
				return (1);
			else
				return (2);
		}
		j++;
	}
	return (0);
}

int	ft_parse_export_arg(char *arg)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	if ((arg[0] < 'A' || arg[0] > 'Z') && (arg[0] < 'a' || arg[0] > 'z'))
		return (1);
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			ret = ft_check_export_key(arg, i);
			if (ret == 1)
				return (1);
			else if (ret == 2)
				return (2);
			else
				return (0);
		}
		i++;
	}
	return (3);
}

char	*ft_remove_plus(char *arg)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(arg));
	while (arg[i])
	{
		if (arg[i] == '+')
			i++;
		tmp[j] = arg[i];
		i++;
		j++;
	}
	tmp[j] = 0;
	free(arg);
	return (tmp);
}

void	ft_export(t_data *data, char *arg)
{
	int	ret;

	ret = 0;
	if (!arg)
	{
		ft_print_export(data);
		return ;
	}
	if (ft_strlen(arg) == 1 && arg[0] == '_')
		return ;
	ret = ft_parse_export_arg(arg);
	if (ret == 0)
	{
		if (!ft_find_key(data, arg))
			data->envp = ft_lstadd_front_env(arg, data->envp);
		else
			ft_add_to_env(data, arg);
	}
	if (ret == 1)
	{
		printf("ERROR\n");
		return ;
	}
	if (ret == 2)
	{
		if (!ft_find_key(data, arg))
		{
			arg = ft_remove_plus(arg);
			data->envp = ft_lstadd_front_env(arg, data->envp);
		}
		else
			ft_add_to_env_plus(data, arg);
	}
	if (ret == 3)
	{
		if (!ft_find_key(data, arg))
			data->envp = ft_lstadd_front_env(arg, data->envp);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:35:22 by achretie          #+#    #+#             */
/*   Updated: 2022/11/19 16:33:09 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_get_key(char *content)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == '=' || content[i] == '+')
			break ;
		i++;
	}
	tmp = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		tmp[j] = content[j];
		j++;
	}
	tmp[j] = 0;
	return (tmp);
}

t_env	*ft_lstnew_env(char *content)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->content = ft_strdup(content);
	list->key = ft_get_key(content);
	list->prev = NULL;
	list->next = NULL;
	return (list);
}

t_env	*ft_lstadd_front_env(char *content, t_env *head)
{
	t_env	*list;

	list = ft_lstnew_env(content);
	list->next = head;
	head->prev = list;
	head = list;
	return (head);
}

t_env	*ft_fill_list(t_env *head, char **envp, int envp_len)
{
	int	i;

	i = envp_len;
	head = ft_lstnew_env(envp[--i]);
	while (i > 0)
		head = ft_lstadd_front_env(envp[--i], head);
	return (head);
}

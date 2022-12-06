/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:04:03 by mafissie          #+#    #+#             */
/*   Updated: 2022/10/29 19:36:26 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"
#include <stdlib.h>

int	init_create_list(t_args **list)
{
	t_args	*tmp;

	tmp = NULL;
	tmp = ft_calloc(1, sizeof(t_args));
	if (tmp == NULL)
		return (-1);
	*list = tmp;
	return (1);
}

int	add_last_list(t_args **list)
{
	t_args	*tmp;
	t_args	*tmp_prev;

	tmp = NULL;
	tmp = (*list);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp_prev = tmp;
	tmp->next = ft_calloc(1, sizeof(t_args));
	if (tmp->next == NULL)
		return (list_free(list));
	tmp = tmp->next;
	tmp->prev = tmp_prev;
	return (1);
}

int	add_prev_list(t_args **list)
{
	t_args	*tmp;

	tmp = NULL;
	tmp = (*list);
	if (tmp == NULL)
		return (-1);
	if (tmp->prev == NULL)
	{
		tmp->prev = ft_calloc(1, sizeof(t_args));
		if (tmp->prev == NULL)
			return (-1);
		tmp->prev->next = tmp;
		return (0);
	}
	else
		return (-1);
}

int add_next_list(t_args **list)
{
	t_args	*tmp;

	tmp = NULL;
	tmp = (*list);
	if (tmp == NULL)
		return (-1);
	if (tmp->next == NULL)
	{
		tmp->next = ft_calloc(1, sizeof(t_args));
		tmp->next->prev = tmp;
		if (tmp->next == NULL)
			return (-1);
		return (0);
	}
	else
		return (-1);
}

int	add_start_list(t_args **list)
{
	t_args	*tmp;
	t_args	*tmp_prev;

	tmp = NULL;
	tmp = (*list);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp_prev = tmp;
	tmp->next = ft_calloc(1, sizeof(t_args));
	if (tmp->next == NULL)
	{
		list_free(list);
		return (-1);
	}
	tmp = tmp->next;
	tmp->prev = tmp_prev;
	ft_indexage_list(list);
	return (1);
}

int	list_free(t_args **list)
{
	t_args	*tmp;

	tmp = NULL;
	tmp = *(list);
	if (tmp == NULL)
		return (-1);
	if (*list == NULL)
		return (-1);
	while ((*list)->next != NULL)
	{
		tmp = tmp->next;
		free((*list)->content);
		(*list)->content = NULL;
		free((*list));
		*list = NULL;
		(*list) = tmp;
	}
	free((*list)->content);
	(*list)->content = NULL;
	free(*list);
	list = NULL;
	return (1);
}

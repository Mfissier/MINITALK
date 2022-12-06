/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:23:23 by mafissie          #+#    #+#             */
/*   Updated: 2022/11/07 18:41:55 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int   begin_duplicate(t_args **tmp, t_args **new_list, char *cpy)
{
	if ((*tmp)->prev == NULL)
	{
		if (add_prev_list(tmp) == -1)
			return (-1);
	}
	else
	{
		(*new_list) = ft_calloc(1, sizeof(t_args));
		if ((*new_list) == NULL)
			return (-1);
		(*new_list)->next = (*tmp);
		(*new_list)->prev = (*tmp)->prev;
		(*tmp)->prev->next = (*new_list);
		(*tmp)->prev = (*new_list);
	}
	(*tmp)->prev->content = cpy;
	return (0);
}

int   next_duplicate(t_args **tmp, t_args **new_list, char *cpy)
{
	if ((*tmp)->next == NULL)
	{
		if (add_next_list(tmp) == -1)
			return (-1);
	}
	else
	{
		(*new_list) = ft_calloc(1, sizeof(t_args));
		if ((*new_list) == NULL)
			return (-1);
		(*new_list)->prev = (*tmp);
		(*new_list)->next = (*tmp)->next;
		(*tmp)->next->prev = (*new_list);
		(*tmp)->next = (*new_list);
	}
	(*tmp)->next->content = cpy;
	return (0);
}

int	create_and_duplicate_args(t_args **args, int idx, int check, char *cpy)
{
	t_args	*new_list;
	t_args	*tmp;

	tmp = NULL;
	tmp = *args;
	new_list = NULL;
	if (tmp == NULL)
		return (-1);
	ft_cd_list(&tmp, args, idx);
	if (check < 0)
	{
		if (begin_duplicate(&tmp, &new_list, cpy) == -1)
			return (-1);
	}
	else if (check > 0)
	{
		if (next_duplicate(&tmp, &new_list, cpy) == -1)
			return (-1);
	}
	else
		tmp->content = cpy;
	ft_indexage_list(args);
	return (idx);
}

int	duplicate_list_with_start_beginning(t_args **args, char *cpy, int i, \
		int check)
{
	if (i == -1)
		return (-1);
	return (create_and_duplicate_args(args, i, check, cpy));
}

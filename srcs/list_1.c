/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:53:09 by mafissie          #+#    #+#             */
/*   Updated: 2022/12/20 04:34:59 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"
#include <stdlib.h>

void	ft_indexage_list(t_args **list)
{
	t_args	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	tmp = (*list);
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	*list = tmp;
	while (tmp->next != NULL)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
	tmp->index = i;
}

void	cpy_list(t_args **l_dst, t_args **l_src)
{
	(*l_dst)->content_test = (*l_src)->content_test;
	(*l_dst)->index_start = (*l_src)->index_start;
	(*l_dst)->index_next = (*l_src)->index_next;
	(*l_dst)->index = (*l_src)->index;
	(*l_dst)->content = (*l_src)->content;
	(*l_dst)->path = (*l_src)->path;
	(*l_dst)->type = (*l_src)->type;
	(*l_src)->content = NULL;
	(*l_src)->path = NULL;
	(*l_dst)->content_test = NULL;
}

int	add_list_index(t_args **list, int i)
{
	t_args	*tmp_content;

	tmp_content = (*list);
	while (tmp_content->next != NULL)
	{
		if (tmp_content->index == i)
			break ;
		tmp_content = tmp_content->next;
	}
	if (tmp_content->index != i)
	{
		ft_putstr_fd("Error index add_list don\'t found !\n", 2);
		return (-1);
	}
	if (tmp_content->next == NULL)
		return (add_last_list(list));
	if (tmp_content->prev == NULL)
	{
		add_start_list(list);
		return (1);
	}
	add_last_list(list);
	while (tmp_content->next != NULL)
		tmp_content = tmp_content->next;
	cpy_list(&tmp_content, &tmp_content->prev);
	while (tmp_content->prev != NULL)
	{
		if (tmp_content->index != i)
			cpy_list(&tmp_content, &tmp_content->prev);
		tmp_content = tmp_content->prev;
	}
	ft_indexage_list(list);
	return (1);
}

void	read_list(t_args **list)
{
	t_args	*tmp;

	tmp = (*list);
	if (tmp == NULL)
		return ;
	while (tmp->next != NULL)
	{
		ft_putstr_fd("struct :[" , 1);
		ft_putnbr_fd(tmp->index, 1);
		if (tmp->content != NULL)
			ft_putstr_fd(tmp->content, 1);
		ft_putstr_fd("]\n" , 1);
		tmp = tmp->next;
	}
	ft_putstr_fd("struct :[" , 1);
	ft_putnbr_fd(tmp->index, 1);
	ft_putstr_fd("]\n" , 1);
}

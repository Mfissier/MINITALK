/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:45:14 by mafissie          #+#    #+#             */
/*   Updated: 2022/11/07 18:49:43 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "./mini.h" 

void	ft_cd_list(t_args **tmp, t_args **source, int i)
{
	t_args	*mv;

	mv = NULL;
	mv = *source;
	if (mv == NULL)
		return ;
	while (mv->next != NULL)
	{
		if (mv->index == i)
			break ;
		mv = mv->next;
	}
	*tmp = mv;
}

void	cpy_create_list(t_args **l_dst, t_args **l_src)
{
	(*l_dst)->content_test = 0;
	(*l_dst)->index_start = 0;
	(*l_dst)->index_next = 0;
	(*l_dst)->index = 0;
	(*l_dst)->content = ft_strdup((*l_src)->content);
	if ((*l_dst)->content == NULL)
		return ;
	(*l_dst)->path = 0;
	(*l_dst)->type = 0;
	(*l_dst)->error = 0;
}

int	handler_list(t_args **list, size_t start, size_t end, int *index)
{
	t_args	*tmp;
	int		idx;
	char	*cpy;

	idx = *index;
	ft_cd_list(&tmp, list, *index);
	cpy = ft_strdup(tmp->content);
	if (cpy == NULL)
	{
		list_free(list);
		exit(2);
	}
	free(tmp->content);
	tmp->content = NULL;
	if (start == 0)
	{
		*index = duplicate_list_with_start_beginning(list, ft_substr(cpy, start, end - start), *index,  0);
		*index = duplicate_list_with_start_beginning(list, ft_substr(cpy, end, ft_strlen(cpy)), *index, 1);
		*index = idx;
	}
	else if (end == (ft_strlen(cpy)))
	{
		*index = duplicate_list_with_start_beginning(list, ft_substr(cpy, start, ft_strlen(cpy)), *index,  0);
		*index = duplicate_list_with_start_beginning(list, ft_substr(cpy, 0, start), *index, -1);
		*index = idx + 1;
	}
	else
	{
		*index = duplicate_list_with_start_beginning(list, ft_substr(cpy, 0, start), *index, -1) + 1;
		*index = duplicate_list_with_start_beginning(list, ft_substr(cpy, start, end - start), *index, 0);
		*index = duplicate_list_with_start_beginning(list, ft_substr(cpy, end, ft_strlen(cpy)), *index, 1);
	}
	if (*index == -1)
	{
		list_free(list);
		free(cpy);
		exit (2);
	}
	free(cpy);
	return (*index);
}

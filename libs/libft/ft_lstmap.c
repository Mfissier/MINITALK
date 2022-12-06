/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 00:20:46 by achretie          #+#    #+#             */
/*   Updated: 2022/04/14 18:01:39 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l;
	t_list	*lst1;

	l = ft_lstnew(f(lst->content));
	if (!l)
		return (NULL);
	lst = lst->next;
	lst1 = l;
	while (lst)
	{
		l = ft_lstnew(f(lst->content));
		if (!l)
		{
			ft_lstclear(&lst, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&lst1, l);
	}
	return (lst1);
}

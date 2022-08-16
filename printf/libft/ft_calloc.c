/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 07:13:26 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/14 23:35:42 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb >= 65535 && size >= 65535)
		return (NULL);
	p = (void *)malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, (nmemb * size));
	return (p);
}

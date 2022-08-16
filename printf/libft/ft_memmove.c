/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:06:49 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/06 22:57:52 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*tmp_d;
	char		*tmp_s;

	if (dest == NULL && src == NULL)
		return (NULL);
	tmp_d = (char *)dest;
	tmp_s = (char *)src;
	if ((void *)tmp_d < (void *)tmp_s)
		while (n--)
			*tmp_d++ = *tmp_s++;
	else
	{
		tmp_d = (char *)dest + (n - 1);
		tmp_s = (char *)src + (n - 1);
		while (n--)
			*tmp_d-- = *tmp_s--;
	}
	return (dest);
}

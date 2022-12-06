/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:56:41 by achretie          #+#    #+#             */
/*   Updated: 2022/04/13 17:34:08 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst1;
	char	*src1;

	dst1 = (char *)dst;
	src1 = (char *)src;
	if (!dst && !src)
		return (dst);
	if (!len)
		return (dst);
	if (dst <= src)
		return (ft_memcpy(dst, src, len));
	while (len--)
		dst1[len] = src1[len];
	return (dst);
}

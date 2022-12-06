/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:56:32 by achretie          #+#    #+#             */
/*   Updated: 2022/04/13 17:36:37 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*str;
	char	*src_char;
	size_t	i;

	if (!dst && !src)
		return (dst);
	i = -1;
	src_char = (char *)src;
	if (n == 0)
		return (dst);
	str = (char *)dst;
	while (++i < n)
		str[i] = src_char[i];
	return (dst);
}

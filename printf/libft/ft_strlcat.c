/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:20:30 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/04 19:05:02 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	srclen = ft_strlen(src);
	if (!size)
		return (srclen);
	while (dst[i] && i < size)
		i++;
	dstlen = i;
	if (i < size)
	{
		while (i < size - 1 && src[j])
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	if (size - 1 < dstlen)
		return (size + srclen);
	return (dstlen + srclen);
}

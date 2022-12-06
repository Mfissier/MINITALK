/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:58:39 by achretie          #+#    #+#             */
/*   Updated: 2022/10/08 01:56:48 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	x;
	size_t	j;

	i = -1;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[++i] && i < len)
	{
		if (str[i] == to_find[0])
		{
			j = i - 1;
			x = -1;
			while (str[++j] == to_find[++x] && j < len)
				if (to_find[x + 1] == '\0')
					return ((char *)str + i);
		}
	}
	return (0);
}

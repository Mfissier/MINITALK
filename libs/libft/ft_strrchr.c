/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:57:56 by achretie          #+#    #+#             */
/*   Updated: 2022/04/05 22:50:40 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	d;

	d = (unsigned char)c;
	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (s[i] == d)
			return (((char *)s) + i);
		i--;
	}
	return (NULL);
}

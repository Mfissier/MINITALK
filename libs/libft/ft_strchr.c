/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:57:49 by achretie          #+#    #+#             */
/*   Updated: 2022/04/05 22:51:26 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	d;

	d = (unsigned char)c;
	i = -1;
	while (s[++i])
		if (s[i] == d)
			return (((char *)s) + i);
	if (s[i] == d)
		return (((char *)s) + i);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:54:06 by achretie          #+#    #+#             */
/*   Updated: 2022/04/11 12:10:33 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*str;

	if (count > 214748367 || size > 214748367 || count * size > 214748367)
		return (0);
	str = malloc(size * count);
	if (!str)
		return (NULL);
	ft_memset(str, 0, size * count);
	return (str);
}

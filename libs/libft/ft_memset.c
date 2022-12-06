/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:56:07 by achretie          #+#    #+#             */
/*   Updated: 2022/04/04 20:14:14 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	size_t	i;
	char	*str;

	str = (char *)pointer;
	i = 0;
	while (count != 0)
	{
		str[i] = value;
		i++;
		count--;
	}
	return (pointer);
}

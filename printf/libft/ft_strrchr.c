/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:15:37 by mafissie          #+#    #+#             */
/*   Updated: 2022/08/16 10:42:44 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*tmp;
	unsigned int	i;

	tmp = (char *)s;
	i = 0;
	if (c == 0)
		return (ft_strchr(s, c));
	if (ft_strchr(tmp, c) == NULL)
		return (NULL);
	while (ft_strchr(tmp, c) != NULL)
	{
		i = (ft_strlen(tmp) - ft_strlen(s)) * -1;
		tmp = ft_strchr(tmp + 1, c);
		if (tmp == NULL)
			return ((char *)s + i);
	}
	return ((char *)s + i);
}

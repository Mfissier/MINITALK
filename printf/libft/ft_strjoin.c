/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:16:51 by mafissie          #+#    #+#             */
/*   Updated: 2022/08/15 21:36:49 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*dest;

	if (!s1)
		return (free(s1), NULL);
	i = -1;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	dest[i] = 0;
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = 0;
	return (free(s1), dest);
}

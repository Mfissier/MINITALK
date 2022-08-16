/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:27:40 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/10 16:37:28 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		str = malloc(sizeof(char) * 1);
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (ft_strlen(s) <= len)
		len = ft_strlen(s) - start;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (s[start] && len--)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

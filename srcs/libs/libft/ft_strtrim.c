/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:59:46 by achretie          #+#    #+#             */
/*   Updated: 2022/04/11 12:09:59 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	check_if_base(char c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		x;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (0);
	while (s1[i] && check_if_base(s1[i], set))
		i++;
	while (j > i && check_if_base(s1[j], set))
		j--;
	str = ft_calloc((j - i + 2), sizeof(char));
	if (!str)
		return (0);
	x = -1;
	while (++x, i + x <= j)
		str[x] = s1[i + x];
	str[x] = 0;
	return (str);
}

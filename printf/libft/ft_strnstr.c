/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:38:59 by mafissie          #+#    #+#             */
/*   Updated: 2022/08/16 10:41:35 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_init_index(size_t *i, size_t *j)
{
	*i = 0;
	*j = 0;
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	ft_init_index(&i, &j);
	if (big == NULL)
		return ((char *)0);
	if (little == NULL || ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i] && (i < len))
	{
		if (big[i] == little[j])
		{
			while ((big[i] == little[j]) && big[i] && (i < len))
			{
				if (!little[j + 1])
					return ((char *)&big[i - j]);
				i++;
				j++;
			}
			i -= j;
			j = 0;
		}
		i++;
	}
	return (NULL);
}

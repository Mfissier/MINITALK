/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:49:54 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/04 19:04:25 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_nbr(long int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*nstr;
	int			i;
	long int	nb;

	nb = n;
	i = ft_size_nbr(nb);
	nstr = ft_calloc((i-- + 1), sizeof(char));
	if (nstr == NULL)
		return (NULL);
	if (nb == 0)
		nstr[i] = '0';
	if (nb < 0)
		nb *= -1;
	while (nb > 0)
	{
		nstr[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		nstr[i] = '-';
	return (nstr);
}

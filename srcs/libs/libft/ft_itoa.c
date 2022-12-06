/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:54:23 by achretie          #+#    #+#             */
/*   Updated: 2022/04/13 17:25:31 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_mem_size(int n, int neg)
{
	int		i;
	char	*str;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	if (neg > 0)
		i++;
	str = ft_calloc(sizeof(char), (i + 1));
	if (!str)
		return (NULL);
	return (str);
}

static char	*ft_tilted(void)
{
	char	*str;

	str = ft_calloc(sizeof(char), 12);
	if (!str)
		return (NULL);
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = 0;
	return (str);
}

static char	*ft_revstr(char *str)
{
	int		i;
	int		j;
	char	temp;
	int		x;

	j = 0;
	temp = 0;
	i = ft_strlen(str) - 1;
	x = i / 2;
	while (j <= x)
	{
		temp = str[j];
		str[j] = str[i];
		str[i] = temp;
		j++;
		i--;
	}
	return (str);
}

static char	*ft_itoa_loop(char *str, int neg, int i, int n)
{
	while (n > 0)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	if (neg == 1)
	{
		str[i] = '-';
		i++;
	}
	str[i] = 0;
	ft_revstr(str);
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		neg;

	if (n == -2147483648)
		return (ft_tilted());
	neg = 0;
	i = 0;
	if (n == 0)
	{
		str = ft_calloc(sizeof(char), 2);
		if (!str)
			return (NULL);
		str[0] = '0';
		return (str);
	}
	if (n < 0)
	{
		n *= -1;
		neg = 1;
	}
	str = ft_mem_size(n, neg);
	str = ft_itoa_loop(str, neg, i, n);
	return (str);
}

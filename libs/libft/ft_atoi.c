/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:58:57 by achretie          #+#    #+#             */
/*   Updated: 2022/03/31 19:30:56 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_atoi_loop(const char *str, int result, int neg, int i)
{
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'\
	|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result += str[i] - '0';
			if (str[i + 1] >= '0' && str[i + 1] <= '9')
				result *= 10;
		}
		else
			return (neg * result);
		i++;
	}
	return (neg * result);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	neg;
	int	ret_value;

	neg = 1;
	result = 0;
	i = 0;
	ret_value = ft_atoi_loop(str, result, neg, i);
	return (ret_value);
}

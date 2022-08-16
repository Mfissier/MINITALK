/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:58:07 by mafissie          #+#    #+#             */
/*   Updated: 2022/08/16 10:41:56 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			neg;
	long int	nb;

	neg = 1;
	nb = 0;
	while (*nptr && (*nptr == '\r' || *nptr == '\f' || *nptr == '\v'
			|| *nptr == '\n' || *nptr == ' ' || *nptr == '\t'))
		nptr++;
	if (*nptr == '-')
	{
		neg = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
		nb = (nb * 10) + *(nptr++) - 48;
	return (nb * neg);
}

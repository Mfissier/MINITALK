/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:51:45 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/14 00:21:24 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../ft_printf.h"

void	ft_init_var(long int *nbr, int n, int *i, int *count)
{
	*nbr = n;
	*i = 0;
	*count = 0;
	if (*nbr <= 0)
		*count = 1;
}

int	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;
	char		tab[20];
	int			i;
	int			count;		

	ft_init_var(&nbr, n, &i, &count);
	if (nbr == 0)
		return (ft_putchar_fd('0', 1));
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr *= -1;
	}
	while (nbr > 0)
	{
		tab[i++] = (nbr % 10) + '0';
		count++;
		nbr /= 10;
	}
	while (i--)
		ft_putchar_fd(tab[i], fd);
	return (count);
}

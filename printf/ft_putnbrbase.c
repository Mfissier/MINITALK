/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:30:37 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/14 23:48:54 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

int	ft_putnbrbase(unsigned long long nbr, t_flag *flag, int base)
{
	char	str[50];
	int		i;

	str[0] = '\0';
	i = 49;
	str[i] = '\0';
	if (nbr == 0)
		return (ft_putstr_fd("0", 1));
	while (nbr >= 1)
	{
		str[--i] = flag->hexascii[nbr % base];
		nbr /= base;
	}
	return (ft_putstr_fd(&str[i], 1));
}

int	ft_putnbrbase_capitaliz(unsigned long long nbr, t_flag *flag, int base)
{
	char	str[50];
	int		i;

	str[0] = '\0';
	i = 49;
	str[i] = '\0';
	if (nbr == 0)
		return (ft_putstr_fd("0", 1));
	while (nbr >= 1)
	{
		str[--i] = flag->hexasciicap[nbr % base];
		nbr /= base;
	}
	return (ft_putstr_fd(&str[i], 1));
}

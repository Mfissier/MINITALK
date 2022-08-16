/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_result.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:52:31 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/16 16:36:47 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_typestr(va_list ap, t_flag *flag)
{
	char	*tmp;

	if (flag->format == 's')
	{
		tmp = va_arg(ap, char *);
		if (tmp == NULL)
			tmp = "(null)";
		return (ft_putstr_fd(tmp, 1));
	}
	else
		return (ft_putchar_fd((char)va_arg(ap, int), 1));
}

int	ft_print_result(va_list ap, t_flag *flag)
{
	long int	nbr;

	if (flag->format == 's')
		return (ft_printf_typestr(ap, flag));
	else if (flag->format == 'c')
		return (ft_printf_typestr(ap, flag));
	else if (flag->format == 'd' || flag->format == 'i')
		return (ft_putnbr_fd(va_arg(ap, int), 1));
	else if (flag->format == 'p')
	{
		nbr = va_arg(ap, long int);
		if (nbr == 0)
			return (ft_putstr_fd("(nil)", 1));
		flag->count += ft_putstr_fd("0x", 1);
		return (ft_putnbrbase(nbr, flag, 16));
	}
	else if (flag->format == 'x')
		return (ft_putnbrbase(va_arg(ap, unsigned int), flag, 16));
	else if (flag->format == 'X')
		return (ft_putnbrbase_capitaliz(va_arg(ap, unsigned int), flag, 16));
	else if (flag->format == 'u')
		return (ft_putnbrbase(va_arg(ap, unsigned int), flag, 10));
	return (0);
}

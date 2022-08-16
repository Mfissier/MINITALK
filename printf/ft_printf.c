/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:25:37 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/15 15:02:31 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_init_struc_flag(t_flag *flag)
{
	flag->count = 0;
	flag->format = '\0';
	flag->hexascii = "0123456789abcdef";
	flag->hexasciicap = "0123456789ABCDEF";
}

int	ft_printf(const char *contains, ...)
{
	va_list	ap;
	char	*str;
	t_flag	flag;

	if (!contains)
		return (-1);
	ft_init_struc_flag(&flag);
	va_start(ap, contains);
	str = (char *)contains;
	while (*str)
	{
		if (*str == '%')
		{
			ft_analysis_flag(++str, &flag);
			if (*str == '%')
				flag.count += ft_putchar_fd(*(str), 1);
			else
				flag.count += ft_print_result(ap, &flag);
			str++;
		}
		else
			flag.count += ft_putchar_fd(*(str++), 1);
	}
	va_end(ap);
	return (flag.count);
}

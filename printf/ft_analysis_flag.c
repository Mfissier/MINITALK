/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analysis_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:01:27 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/16 16:36:14 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_is_flag(char c, t_flag *flag)
{
	if (c == 'c')
		flag->format = 'c';
	else if (c == 's')
		flag->format = 's';
	else if (c == 'p')
		flag->format = 'p';
	else if (c == 'd')
		flag->format = 'd';
	else if (c == 'i')
		flag->format = 'i';
	else if (c == 'u')
		flag->format = 'u';
	else if (c == 'x')
		flag->format = 'x';
	else if (c == 'X')
		flag->format = 'X';
	else
		return (0);
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X')
		return (1);
	return (0);
}

void	ft_analysis_flag(char *str, t_flag	*flag)
{
	while (*str && ft_is_flag(*str, flag))
	{
		if (ft_is_flag(*str, flag))
			str++;
		else
			return ;
	}
}

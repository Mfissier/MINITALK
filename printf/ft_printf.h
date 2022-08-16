/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:26:23 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/14 23:04:14 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include "./libft/libft.h"

typedef struct s_flag
{
	char	format;
	int		count;
	char	*hexascii;
	char	*hexasciicap;
}				t_flag;

int		ft_printf(const char *contain, ...);
void	ft_analysis_flag(char *str, t_flag	*flag);
int		ft_print_result(va_list ap, t_flag	*flag);
int		ft_putnbrbase(unsigned long long nbr, t_flag *flag, int base);
int		ft_putnbrbase_capitaliz(unsigned long long nbr, t_flag *flag, int base);

#endif

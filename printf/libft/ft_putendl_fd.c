/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:44:39 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/07 10:49:53 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
	{
		ft_putchar_fd('\n', fd);
		return ;
	}
	write(fd, s, ft_strlen(s));
	ft_putchar_fd('\n', fd);
}

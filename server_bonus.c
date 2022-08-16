/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:41:41 by mafissie          #+#    #+#             */
/*   Updated: 2022/08/16 11:43:09 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minitalk_bonus.h"

int	ft_print_message(int *c, int *bytes, char **tmp, char **str)
{
	if (*c == 0)
	{
		ft_printf("%s\n", *tmp);
		*c = 0;
		*bytes = 0;
		free(*str);
		*str = NULL;
		free(*tmp);
		*tmp = NULL;
		return (1);
	}
	else
		return (0);
}

void	ft_get_message(int signal, int *statut)
{
	static char	*str;
	static char	*tmp;
	static int	c;
	static int	bytes;

	if (str == NULL)
		str = ft_calloc(2, sizeof(char));
	if (tmp == NULL)
		tmp = ft_calloc(1, sizeof(char));
	if (signal == SIGUSR1)
		c |= 1;
	else if (signal == SIGUSR2)
		c |= 0;
	bytes++;
	if (bytes < 8)
		c <<= 1;
	else
	{
		str[0] = c;
		tmp = ft_strjoin(tmp, str);
		if (ft_print_message(&c, &bytes, &tmp, &str))
			*statut = 0;
		c = 0;
		bytes = 0;
	}
}

void	ft_signal_handler(int sig, siginfo_t *info, void *ignore)
{
	static int	statut;

	statut++;
	if (statut <= 1)
		kill(info->si_pid, SIGUSR1);
	else
	{
		ft_get_message(sig, &statut);
		kill(info->si_pid, SIGUSR1);
	}
	(void)ignore;
	(void)sig;
}

int	main(void)
{
	sigset_t			sigset;
	struct sigaction	sigact;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR2);
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_mask = sigset;
	sigact.sa_sigaction = &ft_signal_handler;
	ft_printf("%d\n", getpid());
	sigaction(SIGUSR2, &sigact, NULL);
	sigaction(SIGUSR1, &sigact, NULL);
	while (1)
		pause();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:49:13 by mafissie          #+#    #+#             */
/*   Updated: 2022/08/16 11:38:02 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minitalk.h"

volatile char	*g_args;

char	*ft_bch(int c)
{
	char	*octet;
	int		bytes;
	int		i;

	octet = ft_calloc(9, sizeof(char));
	bytes = 8;
	i = 0;
	while (--bytes >= 0)
	{
		if (c >> bytes & 1)
			octet[i] = '1';
		else
			octet[i] = '0';
		i++;
		octet[i] = '\0';
	}
	return (octet);
}

void	ft_send_bis(char **octet, int *i, int *index, siginfo_t *info)
{
	int	i_i;
	int	index_index;

	i_i = *i;
	index_index = *index;
	if ((*(*octet + i_i)) == '1')
		kill(info->si_pid, SIGUSR1);
	else if ((*(*octet + i_i)) == '0')
		kill(info->si_pid, SIGUSR2);
	i_i++;
	if (!(*(*octet + i_i)))
	{
		i_i = 0;
		free(*octet);
		*octet = NULL;
		index_index++;
		*i = i_i;
		*index = index_index;
		return ;
	}
	*i = i_i;
	*index = index_index;
}

void	ft_send(int sig, siginfo_t *info, void *ignore)
{
	static char		*octet;
	static int		i;
	static int		index;
	static int		statut;

	if (statut == 0)
		statut = 42;
	if (g_args[index] == '\0')
	{
		kill(info->si_pid, SIGUSR2);
		i++;
		if (i == 8)
			exit(1);
	}
	else
	{
		if (i == 0)
			octet = ft_bch((int)(g_args[index]));
		if (octet[i])
			ft_send_bis(&octet, &i, &index, info);
	}
	(void)sig;
	(void)ignore;
}

void	ft_signal_handler(void)
{
	sigset_t			sigset;
	struct sigaction	sigact;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR1);
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_mask = sigset;
	sigact.sa_sigaction = &ft_send;
	sigaction(SIGUSR1, &sigact, NULL);
	while (1)
		pause();
}

int	main(int ac, char **av)
{
	int	ret;

	if (ac != 3)
		exit(write(2, "Error args\n", ft_strlen("Error args\n")));
	g_args = av[2];
	ret = kill(ft_atoi(av[1]), SIGUSR1);
	if (ret < 0)
		exit(write(2, "Error Pid\n", ft_strlen("Error Pid\n")));
	ft_signal_handler();
	return (0);
}

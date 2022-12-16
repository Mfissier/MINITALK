/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:42:40 by achretie          #+#    #+#             */
/*   Updated: 2022/12/15 20:57:12 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int ret_val = 0;

void	ft_trap(int signal)
{	
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ret_val = 130;
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	char	*input;
	char	*new;
	char	**new_tab;
	t_data	data;
	t_args	*l_args;

	input = NULL;
	new = NULL;
	new_tab = NULL;
	l_args = NULL;
	input = NULL;
	signal(SIGINT, ft_trap);							//Catch le Ctrl + C et relance le prompt via ft_trap 
	signal(SIGQUIT, SIG_IGN);							//Catch le Ctrl + '\' 
	ft_init_data(&data, envp);
	if (ac != 1)
	{
		write(2, "No arguments needed !\n", 23);
		return (0);
	}
	while (1)
	{
		signal(SIGINT, ft_trap);
		signal(SIGQUIT, SIG_IGN);
		if (init_create_list(&l_args) == -1)
			exit (2);
		input = readline("$> ");
		if (!input)
		{
			list_free(&l_args);
			printf("exit\n");
			exit (0);
		}
		add_history(input);
		new = ft_remove_space(input);					//test de parsing, remplace les caracteres par des 0, ceux entre '' par des 1, ceux entre "" par des 2 et les $ entre "" par des 3
		if (new == NULL)
		{
			list_free(&l_args);
			exit (2);
		}
		new_tab = ft_mini_split(new, ' ');
		data.input = ft_strdup(new);
		if (new_tab == NULL)
		{
			list_free(&l_args);
			free(new);
			exit (2);
		}
		free(new);
		new = NULL;
		if (!ft_strncmp(input, "\n", ft_strlen(input)))
		{
			list_free(&l_args);
			free(new);
			continue ;
		}
		check_data_cmd(&l_args, new_tab, envp);
		//test_display_type(&l_args, "main");
		ft_start_commands(&data, l_args);
		list_free(&l_args);
	}
	printf("exit\n");
	return (0);
}

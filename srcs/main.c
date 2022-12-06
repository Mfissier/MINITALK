/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:42:40 by achretie          #+#    #+#             */
/*   Updated: 2022/12/06 14:14:23 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ret_v;												//valeur de return de notre prompt qui sera a actualiser a chaque nouveau prompt

void	ft_trap(int signal)
{	
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ret_v = 130;
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
	ret_v = 0;
	// signal(SIGINT, ft_trap);							//Catch le Ctrl + C et relance le prompt via ft_trap 
	// signal(SIGQUIT, SIG_IGN);							//Catch le Ctrl + '\' 
	if (ac != 1)
	{
		write(2, "No arguments needed !\n", 23);
		return (0);
	}
	while (1)
	{
		if (init_create_list(&l_args) == -1)
			exit (2);
		input = readline("$> ");
		// input = ft_strdup("||||  sjkdfh jkjhskdjfhsjk jksdfh kfjksd | sjkdf << echo");
		if (!input)
		{
			list_free(&l_args);
			printf("exit\n");
			exit (0);
		}
		// ft_start_exec(&data, envp); 					//test pour exec une commande
		if (!ft_strncmp(input, "exit", 4))			//test pour exit, exit marche aussi avec "       exit       "
		{
			list_free(&l_args);
			break ;
		}
		if (!ft_strncmp(input, "env", 3))				//test pour env
			ft_env(&data);
		if (!ft_strncmp(input, "pwd", 3))				//test pour env
			ft_pwd();
		// add_history(input);
		new = ft_remove_space(input);					//test de parsing, remplace les caracteres par des 0, ceux entre '' par des 1, ceux entre "" par des 2 et les $ entre "" par des 3
		if (new == NULL)
		{
			list_free(&l_args);
			exit (2);
		}
		new_tab = ft_mini_split(new, ' ');
		if (new_tab == NULL)
		{
			list_free(&l_args);
			free(new);
			exit (2);
		}
		free(new);
		// free(input);
		// input = NULL;
		new = NULL;
		// for (int y = 0; new_tab[y]; y++)
		// 	printf("y = %d : %s\n", y, new_tab[y]);
		check_data_cmd(&l_args, new_tab, envp);
		test_display_type(&l_args, "main");
		list_free(&l_args);
	}
	printf("exit\n");
	return (0);
}

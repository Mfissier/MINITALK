/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:13:52 by achretie          #+#    #+#             */
/*   Updated: 2022/12/20 09:20:28 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_unset(t_data *data, char *var)
{
	t_env	*save;
	t_env	*tmp;

	save = data->envp;
	if (ft_strncmp(data->envp->content, var, ft_strlen(var)) == 0 && ft_strlen(var) == ft_strlen(data->envp->key))
	{
		tmp = data->envp;
		data->envp = data->envp->next;
		free(tmp);
		return ;
	}
	while (data->envp->next)
	{
		if (ft_strncmp(data->envp->next->content, var, ft_strlen(var)) == 0 && ft_strlen(var) == ft_strlen(data->envp->next->key))
		{
			tmp = data->envp->next;
			data->envp->next = tmp->next;
			free(tmp);
			break ;
		}
		data->envp = data->envp->next;
	}
	data->envp = save;
}

void	ft_echo(t_args *args)
{
	t_args	*tmp;

	tmp = args;
	if (!args->next)
		return ;
	if (!ft_strncmp(args->next->content, "-n", ft_strlen(args->next->content)))
	{
		args = args->next;
		while (args->next)
		{
			printf("%s", args->next->content);
			args = args->next;
			if (args->content)
				printf(" ");
		}
	}
	else
	{
		while (args->next)
		{
			printf("%s", args->next->content);
			args = args->next;
			if (args->content)
				printf(" ");
		}
		printf("\n");
	}
	args = tmp;
}

void	ft_pwd(void)
{
	char	buffer[10000];

	getcwd(buffer, 10000);
	printf("%s\n", buffer);
}

int	ft_cd(t_data *data) //Penser a verifier si les $var sont accessibles et on pas etait unset ?
{
	char	str[10000];
	char	*stock;
	char	*old_pwd;

	old_pwd = ft_getenv(data, "PWD");
	if (!data->cd_str) //cd sans argument, renvoie a HOME
	{
		stock = ft_getenv(data, "HOME");
		if (chdir(stock) == -1)
		{
			free(stock);
			return (-1);
		}
		ft_setenv(data, "PWD", stock);
	}
	else
	{
		if (chdir(data->cd_str) == -1)
		{
			printf("cd: no such file or directory: %s\n", data->cd_str);
			free(old_pwd);
			return (-1);
		}
		getcwd(str, 10000);
		ft_setenv(data, "PWD", str);
	}
	ft_setenv(data, "OLDPWD", old_pwd);
	return (0);
}

int	ft_exit(t_args *args, t_data *data)
{
	(void)data;
	list_free(&args);
	//free_data();
	printf("exit\n");
	exit (0);
}

void	ft_heredoc(t_data *data, char *delim)
{
	char	*input;
	char	*stock;

	if (!delim || !*delim)
		return;
	stock = ft_calloc(sizeof(char), 1);
	if (!stock)
		return ;
	while (1)
	{
		data->idoc++;
		input = readline("> ");
		if (!input)
		{
			printf("Minishell: warning: here-document at line %d delimited by end-of-file (wanted \'%s\')\n", data->idoc, delim);
			break ;
		}
		if (!ft_strncmp(input, delim, ft_strlen(delim)))
			break ;
		stock = ft_strjoin(stock, input);
		if (!stock)
			break;
		stock = ft_strjoin(stock, "\n");
		if (!stock)
			break;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:39:27 by achretie          #+#    #+#             */
/*   Updated: 2022/12/06 14:16:07 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// METACARACTERES space, tab, newline, ‘|’, ‘&’, ‘(’, ‘)’, ‘<’, or ‘>’

char	*ft_parse_input(char *input)
{
	char	*deep;
	int		i;

	deep = NULL;
	i = 0;
	deep = ft_strdup(input);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (input[i] == '\'')
			{
				deep[i] = '0';
				i++;
				while (input[i] && (input[i] != '\''))
				{
					deep[i] = '1';
					i++;
				}
				deep[i] = '0';
			}
			else if (input[i] == '\"')
			{
				deep[i] = '0';
				i++;
				while (input[i] && (input[i] != '\"'))
				{
					if (input[i] == '$')
						deep[i] = '3';
					else
						deep[i] = '2';
					i++;
				}
				deep[i] = '0';
			}
		}
		else
			deep[i] = '0';
		i++;
	}
	deep[i] = 0;
	return (deep);
}
// char	**ft_path_declared(char *cmd)
// {
// 	char	**sstr;
// 	int		i;
// 	int		count;

// 	count = 0;
// 	sstr = NULL;
// 	i = 0;
// 	sstr = ft_calloc(2, sizeof(sstr));
// 	while (cmd[i])
// 	{
// 		while (cmd[i] == '.')
// 		{
// 			if ((ft_strlen((cmd + i)) > 1) && (cmd[i + 1] == '.'))
// 				i += 2;
// 			else
// 				i++;
// 			if ((ft_strlen((cmd + i)) > 1)
// 				&& ((cmd[i] == '.') && cmd[i + 1] == '/'))
// 				i++;
// 		}
// 		count++;
// 		i++;
// 	}
// }

int    ft_try_access(char *cmd, char **envp)
{
	char	**path;
	char	*word;
	char	*full_word;
	int		i;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		if (access(cmd, F_OK) == 0)
			return (1);
		else
			return (0);
	}
	path = ft_parse_path(envp);
	i = -1;
	while (path[++i])
	{
		word = ft_strjoin(path[i], "/");
		if (word == NULL)
		{
			ft_free_path(path);
			return (-1);
		}
		full_word = ft_strjoin(word, cmd);
		if (full_word == NULL)
		{
			free(word);
			ft_free_path(path);
			return (-1);
		}
		if (access(full_word, F_OK) == 0)
		{
			free(word);
			ft_free_path(path);
			return (1);
		}
		free(word);
		free(full_word);
	}
	ft_free_path(path);
	return (0);
}

char	*ft_parse_input_mini(char *input)
{
	char	*deep;
	int		i;

	i = 0;
	deep = NULL;
	deep = ft_calloc(sizeof(char), ft_strlen(input) + 1);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (input[i] == '\'')
			{
				deep[i] = '1';
				i++;
				while (input[i] && (input[i] != '\''))
				{
					deep[i] = '1';
					i++;
				}
				deep[i] = '1';
			}
			else if (input[i] == '\"')
			{
				deep[i] = '2';
				i++;
				while (input[i] && (input[i] != '\"'))
				{
					if (input[i] == '$')
						deep[i] = '3';
					else
						deep[i] = '2';
					i++;
				}
				deep[i] = '2';
			}
		}
		else
			deep[i] = '0';
		i++;
	}
	deep[i] = 0;
	return (deep);
}

static char	*ft_clean_quotes(char *s)
{
	/*int		count_dq;
	int		count_sq;
	int		j;

	j = 0;
	i = 0;
	count_dq = 0;
	count_sq = 0;
	new_s = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	while (s[i])
	{
		if (s[i] == '\'')
			count_sq++;
		else if (s[i] == '\"')
			count_dq++;
		else
			new_s[j++] = s[i];
		i++;
	}
	new_s[j] = 0;
	if (count_sq % 2 != 0 || count_sq % 2 != 0)
	{
		free (new_s);
		return (NULL);
	}*/
	int		i;
	int		j;
	char	*new_s;
	char	*level;

	level = ft_parse_input(s);
	i = 0;
	j = 0;
	new_s = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	while (s[i])
	{
		if (level[i] == '0' && s[i] != '\'' && s[i] != '\"')
			new_s[j++] = s[i];
		else if (level[i] == '1')
			new_s[j++] = s[i];
		else if (level[i] == '2')
			new_s[j++] = s[i];
		i++;
	}
	new_s[j] = 0;
	free(level);
	return (new_s);
}

static	int	ft_check_redirect(char *new_tab)
{
	if (!strcmp(new_tab, "<") && ft_strlen(new_tab) == 1)
		return (1);
	if (!strcmp(new_tab, ">") && ft_strlen(new_tab) == 1)
		return (1);
	if (!strcmp(new_tab, "<<") && ft_strlen(new_tab) == 2)
		return (1);
	if (!strcmp(new_tab, ">>") && ft_strlen(new_tab) == 2)
		return (1);
	if (!strcmp(new_tab, "<>") && ft_strlen(new_tab) == 2)
		return (1);
	return (0);
}

/*static int	ft_check_quotes(char *new_tab)
{
	int	i;

	i = 0;
	while (new_tab[i])
	{
		if (new_tab[i] == '\'')
		{
			while (new_tab[++i])
			{
				if (new_tab[i] == '\"')
					return (1);
				if (new_tab[i] == '\'')
					break ;
			}
		}
		else if (new_tab[i] == '\"')
		{
			while (new_tab[++i])
			{
				if (new_tab[i] == '\'')
					return (1);
				if (new_tab[i] == '\"')
					break ;
			}
		}
		i+
	return (0);
}*/

int	ft_verify_cmd(t_args *l_args, char	**new_tab, char **envp)
{
	char	*s;

	(void)l_args;
	if (ft_check_redirect(new_tab[0]))
	{
		printf("valid redirection\n");
		return (0);
	}
	/*if (ft_check_quotes(new_tab[0]))
	{
		printf("WRONG QUOTES\n");
		return (0);
	}*/
	s = ft_clean_quotes(new_tab[0]); //garder les quotes imbriques dans les autres
	if (!s)
	{
		printf("wrong quotes\n");
		return (-1);
	}
	else
	{
		if (ft_try_access(s, envp))
			printf("command success\n");
		else
			printf("command failed\n");
	}
	return (0);
}

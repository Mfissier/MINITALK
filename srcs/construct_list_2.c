/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_list_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:51:37 by mafissie          #+#    #+#             */
/*   Updated: 2022/11/07 18:59:37 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

char	*cmd_clean(char *str)
{
	int		i;
	int		count;
	char	*new_cmd;

	new_cmd = NULL;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			count++;
		}
		i++;
	}
	i = 0;
	new_cmd = ft_calloc(count + 1, sizeof(char));
	count = 0;
	if (new_cmd == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new_cmd[count++] = str[i];
		i++;
	}
	if (new_cmd[0] == '\0')
	{
		free(new_cmd);
		return (NULL);
	}
	return (new_cmd);
}

int	construct_builtins_cmd(t_args **list, int *index)
{
	char	*new_cmd;
	(void)index;
	if ((*list)->type != 0 && (*list)->type != WRITE)
		return (0);
	new_cmd = cmd_clean((*list)->content);
	if (new_cmd == NULL)
		return (-1);
	if (access(new_cmd, F_OK) == 0)
		(*list)->type = CMD;
	if (ft_strstr(new_cmd, "echo") || ft_strstr(new_cmd, "cd")
		|| ft_strstr(new_cmd, "pwd")
		|| ft_strstr(new_cmd, "export")
		|| ft_strstr(new_cmd, "unset")
		|| ft_strstr(new_cmd, "env")
		|| ft_strstr(new_cmd, "exit"))
		(*list)->type = BUILTINS;
	else
		(*list)->type = CMD;
	free(new_cmd);
	*index = 0;
	return (1);
}

int	construct_env(t_args **list, int *index, t_args **args)
{
	(void)index;
	(void)args;
	if (identify_parse((*list)->content, NULL, ENV) != ENV)
		return (0);
	else
		(*list)->type = ENV;
	*index += 1;
	return (1);
}

int	construct_great(t_args **list, int *index, t_args **args)
{	
	int	check;
	int	start;
	int	end;

	ft_cd_list(list, args, *index);
	if (identify_parse((*list)->content, ">", GREAT) != GREAT)
		return (0);
	check = 0;
	if (!take_flag(&start, &end, list, ">") && ft_strlen((*list)->content) != ft_strlen(">"))
		return (-1);
	else if ((*list)->type == 0)
	{
		if (ft_strlen(">") != ft_strlen((*list)->content))
			check = handler_list(args, start, end, index);
		else
			check = *index;
		if (check == -1)
			return (-1);
		ft_cd_list(list, args, check);
		(*list)->type = GREAT;
		*index = 0;
		return (1);
	}
	*index += 1;
	return (1);
}

int	construct_d_great(t_args **list, int *index, t_args **args)
{
	int	check;
	int	start;
	int	end;

	ft_cd_list(list, args, *index);
	if (identify_parse((*list)->content, ">>", D_GREAT) != D_GREAT)
		return (0);
	check = 0;
	if (!take_flag(&start, &end, list, ">>")  && ft_strlen((*list)->content) != ft_strlen(">>"))
		return (-1);
	else if ((*list)->type == 0)
	{
		if (ft_strlen(">>") != ft_strlen((*list)->content))
			check = handler_list(args, start, end, index);
		else
			check = *index;
		if (check == -1)
			return (-1);
		ft_cd_list(list, args, check);
		(*list)->type = D_GREAT;
		*index = 0;
		return (1);
	}
	*index += 1;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_list_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:51:32 by mafissie          #+#    #+#             */
/*   Updated: 2022/11/07 18:51:33 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	construct_less(t_args **list, int *index, t_args **args)
{
	int	check;
	int	start;
	int	end;

	ft_cd_list(list, args, *index);
	if (identify_parse((*list)->content, "<", LESS) != LESS)
		return (0);
	check = 0;
	if (!take_flag(&start, &end, list, "<") && ft_strlen((*list)->content) != ft_strlen("<"))
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
		(*list)->type = LESS;
		*index = 0;
		return (1);
	}
	*index += 1;
	return (1);
}

int	construct_d_less(t_args **list, int *index, t_args **args)
{
	int	check;
	int	start;
	int	end;

	ft_cd_list(list, args, *index);
	if (identify_parse((*list)->content, "<<", D_LESS) != D_LESS)
		return (0);
	check = 0;
	if (!take_flag(&start, &end, list, "<<") && ft_strlen((*list)->content) != ft_strlen("<<"))
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
		(*list)->type = D_LESS;
		*index = 0;
		return (1);
	}
	*index += 1;
	return (1);
}

int	construct_pipe(t_args **list, int *index, t_args **args)
{
	int	check;
	int	start;
	int	end;

	ft_cd_list(list, args, *index);
	if (identify_parse((*list)->content, "|", PIPE) != PIPE)
		return (0);
	check = 0;
	if (!take_flag(&start, &end, list, "|") && ft_strlen((*list)->content) != ft_strlen("|"))
		return (-1);
	else if ((*list)->type == 0)
	{
		if (ft_strlen("|") != ft_strlen((*list)->content))
			check = handler_list(args, start, end, index);
		else
			check = *index;
		if (check == -1)
			return (-1);
		ft_cd_list(list, args, check);
		(*list)->type = PIPE;
		*index = 0;
		return (1);
	}
	*index += 1;
	return (1);
}

int	construct_new_path(t_args **list, int *index, t_args **args)
{
	(void)index;
	(void)args;
	if (identify_parse((*list)->content, NULL, NEW_PATH) != NEW_PATH)
		return (0);
	if ((*list)->type >= 0)
		return (0);
	else
		(*list)->type = NEW_PATH;
	*index += 1;
	return (1);
}

int	construct_cmd_opt(t_args **list, int *index, t_args **args)
{
	(void)index;
	(void)args;
	if ((*list)->type >= 0)
		return (0);
	else
		(*list)->type = CMD_OPT;
	*index += 1;
	return (1);
}

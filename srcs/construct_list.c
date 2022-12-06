/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:39:09 by mafissie          #+#    #+#             */
/*   Updated: 2022/11/07 18:59:57 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"
int	flag_is_ok(char *content, int start, int end, char hook)
{
	int	left_count;
	int	right_count;

	left_count = 0;
	right_count = 0;
	while(start >= 0)
	{
		if (content[start] == '"' || content[start] == '\'')
		{
			hook = content[start];
			left_count++;
			if (content[start] == hook) {
				while(--start >= 0)
				{
					if (content[start] == hook)				
						left_count++;
				}
			} 
			else
				start--;
		}
		else
			start--;
	}
	while(content[++end])
	{
		if (content[start] == '"' || content[start] == '\'')
		{
			hook = content[start];
			right_count++;
			while(content[++end])
			{
				if (content[end] == hook)
					right_count++;
			}	
		}
	}
	if (right_count == 1 || right_count % 2 == 1)
		return (0);
	else if (left_count == 1 || left_count % 2 == 1)
		return (0);
	else
		return (1);
}

int	take_flag(int *start, int *end, t_args **list, char *flag)
{
	int		i;
	char	hook;

	hook = 0;
	*start = ft_strstr((*list)->content, flag) - (*list)->content;
	*end = *start + ft_strlen(flag);
	i = *start;
	if (!((i - 1) < 0) && !(*end > (int)ft_strlen((*list)->content)))
	{
		if (flag_is_ok((*list)->content, (*start - 1), (*end - 1), hook))
			return (1);
		else
		{
			*start += ft_strlen(flag);
			while (ft_strstr(((*list)->content + (*start)), flag))
			{
				*start = ft_strstr(((*list)->content + (*start)), flag) - (*list)->content;
				*end = *start + ft_strlen(flag);
				if (flag_is_ok((*list)->content, (*start - 1), (*end - 1), hook))
					return (1);
				*start += ft_strlen(flag);
			}
		}
	}
	else
		return (1);
	return (0);
}

int	take_parse_write(int *start, int *end, t_args **list)
{
	char	*str;
	size_t	i;
	int		hook;

	str = (*list)->content;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (str[i] == '"')
				hook = str[i];
			if (str[i] == '\'')
				hook = str[i];
			*start = i++;
			while (str[i] && (str[i] != hook) && (i != 0 && ((str[i - 1] != '\\') && str[i] != hook)))
				i++;
			if (*start == 0 && ((i + 1) == ft_strlen(str)))
				return (0);
			*end = i + 1;
			return (1);
		}
	}
	return (0);
}

int	construct_write(t_args **list, int *index, t_args **args)
{
	int	start;
	int	end;
	int check;

	check = 0;
	start = 0;
	end = 0;
	ft_cd_list(list, args, *index);
	if ((*list)->type == 0)
		return (0);
	// if (identify_parse_write((*list)->content) != WRITE)
	// 	return (0);
	if (take_parse_write(&start, &end, list))
	{
		check = handler_list(args, start, end, index);
		if (check == -1)
			return (-1);
		ft_cd_list(list, args, check);
		(*list)->type = WRITE;
		*index = 0;
		return (1);
	}
	*index += 1;
	return (1);
}

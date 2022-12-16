/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:56:04 by achretie          #+#    #+#             */
/*   Updated: 2022/12/12 02:01:48 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_remove_space_bis(int *i, int *j, char **input, char **new)
{
	if ((*input)[*i] == '\'' )
	{
		(*new)[(*j)++] = (*input)[(*i)++];
		while ((*input)[*i] && ((*input)[*i] != '\''))
			(*new)[(*j)++] = (*input)[(*i)++];
	}
	else
	{
		(*new)[(*j)++] = (*input)[(*i)++];
		while ((*input)[*i] && ((*input)[*i] != '\"'))
			(*new)[(*j)++] = (*input)[(*i)++];
	}
}

char	*ft_remove_space(char *input)
{
	int		i;
	int		j;
	char	*new;
	char	*tmp_input;

	tmp_input = NULL;
	new = NULL;
	i = 0;
	j = 0;
	input = ft_strtrim(input, " ");
	tmp_input = ft_strtrim(input, " ");
	new = ft_strdup(tmp_input);
	while (tmp_input[i])
	{
		if (tmp_input[i] == '\'' || tmp_input[i] == '\"')
			ft_remove_space_bis(&i, &j, &tmp_input, &new);
		if (tmp_input[i] == ' ')
			new[j] = ' ';
		new[j] = tmp_input[i];
		i++;
		j++;
	}
	new[i] = 0;
	free(tmp_input);
	return (new);
}

static size_t	ft_find_number(const char *s, char c)
{
	size_t	i;
	size_t	count;
	char	*level;

	level = NULL;
	level = ft_parse_input((char *)s);
	count = 0;
	i = 0;
	if (s[0] != c)
		count++;
	while (s[++i])
		if (s[i] != c && s[i - 1] == c && level[i] == '0')
			count++;
	free(level);
	return (count);
}

static char	**ft_fill_tab(char **t, char const *s, char c, size_t nb_word)
{
	size_t		word_len;
	size_t		j[2];
	size_t		start;
	size_t		i;
	char		*level;

	level = NULL;
	level = ft_parse_input_mini((char *)s);
	i = 0;
	j[1] = 0;
	j[0] = 0;
	word_len = 0;
	while (j[1] < nb_word)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
		{
			if (level[i] != '0')
			{
				while (level[i] != '0' && level[i])
				{
					i++;
					word_len++;
				}
			}
			else
			{
				word_len++;
				i++;
			}
		}
		t[j[1]] = malloc(sizeof(char) * word_len + 1);
		while (j[0] < word_len)
			t[j[1]][j[0]++] = s[start++];
		t[j[1]++][j[0]] = '\0';
		j[0] = 0;
		word_len = 0;
	}
	t[j[1]] = NULL;
	free(level);
	return (t);
}

static char	*ft_fill_string(char const *str)
{
	int		i;
	char	*s;

	i = -1;
	s = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[++i])
		s[i] = (char)str[i];
	s[i] = 0;
	return (s);
}

char	**ft_mini_split(char const *s, char c) //Garder les ; et '\' apres le split
{
	char		**t;
	size_t		nb_word;
	char const	*temp;

	t = NULL;
	nb_word = 0;
	temp = s;
	if (s[0] == 0)
	{
		t = malloc(sizeof(char *) * 1);
		t[0] = NULL;
		return (t);
	}
	else if (!c)
	{
		t = malloc(sizeof(char *) * 2);
		t[0] = ft_fill_string(s);
		t[1] = NULL;
		return (t);
	}
	nb_word = ft_find_number(temp, c);
	t = malloc(sizeof(char *) * (nb_word + 1));
	if (!t)
		return (NULL);
	t = ft_fill_tab(t, s, c, nb_word);
	return (t);
}

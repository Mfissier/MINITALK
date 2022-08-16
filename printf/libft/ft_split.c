/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:35:22 by mafissie          #+#    #+#             */
/*   Updated: 2022/04/09 20:57:26 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_wordfree(char **tab, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

static char	*ft_wordtab(const char *s, char c, char **str)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	*str = malloc(sizeof(char) * (i + 1));
	if (*str == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		*(*str + i) = s[i];
		i++;
	}
	*(*str + i) = '\0';
	return (*str);
}

static int	ft_wordnbr(char const *s, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (s[i] && (s[i] == c))
		i++;
	while (s[i])
	{
		if (s[i] && (s[i] != c))
		{
			word++;
			while (s[i] && (s[i] != c))
				i++;
		}
		else
			i++;
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	tab = malloc(sizeof(*tab) * (ft_wordnbr(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s && *s != c)
		{
			if (!ft_wordtab(s, c, &tab[i++]))
				return (ft_wordfree(tab, i));
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	tab[i] = NULL;
	return (tab);
}

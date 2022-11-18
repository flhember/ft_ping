/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:45:15 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:07:59 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_word(char const *s, char c)
{
	int		i;
	int		res;

	res = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			res++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (res);
}

static char		**remplissage(char **tab, char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			tab[k] = ft_strsub(s, (unsigned int)j, i - j);
			k++;
		}
		else
			i++;
	}
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	int		nbword;
	char	**tabfinal;

	tabfinal = NULL;
	if (!c || !s)
		return (NULL);
	nbword = count_word(s, c);
	if (!(tabfinal = (char**)malloc(sizeof(char*) * (nbword + 1))))
		return (0);
	tabfinal = remplissage(tabfinal, s, c);
	tabfinal[nbword] = NULL;
	return (tabfinal);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:08:43 by flhember          #+#    #+#             */
/*   Updated: 2019/05/02 17:28:59 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_check(char *str)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '%' && str[i + 1] == '%')
		{
			tmp = ft_strsub(str, 0, i);
			tmp2 = ft_strsub(str, i + 1, ft_strlen(str) - i);
			ft_strdel(&str);
			str = ft_strjoinfree(tmp, tmp2, 3);
		}
		i++;
	}
	return (str);
}

char		**ft_check_percent(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		tab[i] = ft_check(tab[i]);
		i++;
	}
	return (tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:59:41 by flhember          #+#    #+#             */
/*   Updated: 2019/05/06 17:55:29 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

long long		ft_print_tab(char **tab, int i)
{
	char		*str_space;
	long long	size_tab;

	str_space = NULL;
	size_tab = 0;
	while (tab[i])
	{
		if (ft_strlen(tab[i]) > 1 && tab[i][ft_strlen(tab[i]) - 1] == 'c'
				&& tab[i][ft_strlen(tab[i]) - 2] == '%')
		{
			if ((ft_strlen(tab[i]) - 2) != 0)
			{
				str_space = ft_strsub(tab[i], 0, ft_strlen(tab[i]) - 2);
				ft_putstr(str_space);
				ft_strdel(&str_space);
			}
			ft_putchar('\0');
			size_tab--;
		}
		else
			ft_putstr(tab[i]);
		size_tab += ft_strlen(tab[i]);
		i++;
	}
	return (size_tab);
}

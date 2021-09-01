/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 12:22:17 by flhember          #+#    #+#             */
/*   Updated: 2019/05/06 12:33:13 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	**ft_convert_param(char **tab, t_conv **list, va_list ap)
{
	int		j;
	int		flag;
	t_conv	*tmp;

	tmp = *list;
	j = 0;
	while (tab[j])
	{
		flag = 0;
		if (tab[j][0] == '%' && tab[j][1] != '%')
		{
			while (!flag && tmp)
			{
				if (!flag && tmp->type == tab[j][(ft_strlen((tab[j]))) - 1])
				{
					tab[j] = tmp->f(ap, tab[j]);
					flag++;
				}
				tmp = tmp->next;
			}
			tmp = *list;
		}
		j++;
	}
	return (tab);
}

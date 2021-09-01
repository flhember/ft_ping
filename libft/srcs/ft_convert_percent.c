/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:56:01 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:19:13 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_filling(t_option **list, char *str)
{
	int		i;

	i = 0;
	if ((*list)->min)
	{
		str = ft_strnewspace((*list)->min);
		if ((*list)->minus)
			str[0] = '%';
		else
		{
			str[(*list)->min - 1] = '%';
			if ((*list)->zero)
				while (str[i] != '%')
					str[i++] = '0';
		}
	}
	else
	{
		str = ft_strnewspace(1);
		str[0] = '%';
	}
	return (str);
}

char		*ft_convert_percent(va_list ap, char *str)
{
	t_option	*list;

	if (ap)
		list = NULL;
	list = ft_get_option(str);
	ft_strdel(&str);
	str = ft_filling(&list, str);
	ft_free_option(&list);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:32:16 by flhember          #+#    #+#             */
/*   Updated: 2019/05/06 15:09:12 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_filling(char var, t_option **list)
{
	size_t	i;
	char	*str;

	i = 0;
	if ((*list)->min)
		str = ft_strnewspace((*list)->min);
	else
		str = ft_memalloc(2);
	if ((*list)->minus)
	{
		str[0] = var;
		return (str);
	}
	else if ((*list)->zero)
	{
		while (i < (*list)->min)
			str[i++] = '0';
		str[i - 1] = var;
	}
	else
	{
		i = ft_strlen(str);
		str[i - 1] = var;
	}
	return (str);
}

static char	*ft_null_param(t_option **list, char *str)
{
	ft_strdel(&str);
	if ((*list)->min > 1)
	{
		str = ft_strnewspace((*list)->min + 1);
		str[(*list)->min] = 'c';
		str[(*list)->min - 1] = '%';
	}
	else
		str = ft_strdup("%c");
	ft_free_option(list);
	return (str);
}

char		*ft_convert_c(va_list ap, char *str)
{
	t_option	*list;
	int			tmp;

	list = NULL;
	tmp = va_arg(ap, int);
	list = ft_get_option(str);
	if (tmp == 0)
		return (ft_null_param(&list, str));
	if (str[1] == 'c')
	{
		ft_free_option(&list);
		ft_strdel(&str);
		if (!(str = ft_memalloc(2)))
			return (NULL);
		str[0] = tmp;
		return (str);
	}
	ft_strdel(&str);
	str = ft_filling(tmp, &list);
	ft_free_option(&list);
	return (str);
}

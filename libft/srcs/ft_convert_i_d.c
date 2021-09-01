/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_i_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:34:11 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:13:18 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*ft_filling(char *str, char *var, t_option **list)
{
	size_t		size_var;

	size_var = ft_strlen(var);
	if (var[0] == '-')
		size_var--;
	if ((*list)->minus && ((*list)->zero || ((*list)->prec > (int)size_var)))
		str = ft_put_zero_minus(str, var, list);
	if (!(*list)->minus && ((*list)->zero || ((*list)->prec > (int)size_var)))
		str = ft_put_zero(str, var, list);
	str = ft_put_signe(str, var, list, size_var);
	str = ft_put_num(str, var, list, size_var);
	return (str);
}

static size_t	ft_find_good_size_bis(char *var, t_option **list, size_t size)
{
	if ((*list)->prec > (int)(*list)->min &&
			(*list)->prec >= (int)ft_strlen(var))
	{
		size = (*list)->prec;
		if (var[0] == '-' || (var[0] == '-' && ((*list)->minus ||
						(*list)->space || (*list)->zero || (*list)->plus)))
			size++;
	}
	else
		size = ft_strlen(var);
	if ((var[0] != '-' && ((*list)->space || ((*list)->plus))))
		size++;
	return (size);
}

static size_t	ft_find_good_size(char *var, t_option **list, size_t size)
{
	if (var[0] == '0' && var[1] == '\0' &&
			(*list)->prec == -1 && (*list)->min == 0)
	{
		if ((var[0] != '-' && ((*list)->space || ((*list)->plus))))
			return (1);
		return (0);
	}
	if (var[0] != '0' && var[1] != '\0' && (*list)->prec == -1)
		(*list)->prec++;
	if ((int)(*list)->min >= (*list)->prec && (*list)->min > ft_strlen(var))
	{
		size = (*list)->min;
		if (var[0] == '-' && (int)(*list)->min == (*list)->prec)
			size += 1;
		return (size);
	}
	else
		size = ft_find_good_size_bis(var, list, size);
	return (size);
}

char			*ft_convert_i_d(va_list ap, char *str)
{
	t_option	*list;
	char		*var;
	char		*strfinal;
	size_t		size_malloc;

	list = NULL;
	size_malloc = 0;
	strfinal = NULL;
	if (str[1] == 'i' || str[1] == 'd')
	{
		ft_strdel(&str);
		str = ft_itoa(va_arg(ap, int));
		return (str);
	}
	list = ft_get_option(str);
	var = ft_get_good_size_signed(ap, &list);
	size_malloc = ft_find_good_size(var, &list, size_malloc);
	strfinal = ft_strnewspace(size_malloc);
	if (strfinal)
		strfinal = ft_filling(strfinal, var, &list);
	ft_free_option(&list);
	ft_strdel(&var);
	ft_strdel(&str);
	return (strfinal);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:28:23 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:10:08 by flhember         ###   ########.fr       */
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
	if ((*list)->prec == -1)
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

static char		*ft_check_spec(char *str, char *var, t_option **list, int i)
{
	int			size_var;

	i = -1;
	size_var = ft_strlen(var);
	if (var[size_var - 1] != '.' && (var[size_var - 1] > '9'
				|| var[size_var - 1] < '0'))
	{
		if ((*list)->min > (size_t)size_var)
			str = ft_strnewspace((*list)->min);
		else
			str = ft_strnewspace(size_var);
	}
	if (str)
	{
		if ((*list)->minus)
			while (i++ < size_var - 1)
				str[i] = var[i];
		else
		{
			i = ft_strlen(str);
			while (size_var >= 0)
				str[i--] = var[size_var--];
		}
	}
	return (str);
}

char			*ft_convert_f(va_list ap, char *str)
{
	t_option	*list;
	char		*var;
	size_t		size;
	char		*str_final;

	size = 0;
	var = NULL;
	str_final = NULL;
	list = ft_get_option(str);
	if (str[1] == 'f')
	{
		ft_free_float(&list, str, var);
		return (ft_ftoa_dbl(va_arg(ap, double), 6, 0));
	}
	var = ft_good_var(ap, &list);
	if ((str_final = ft_check_spec(str_final, var, &list, size)))
	{
		ft_free_float(&list, str, var);
		return (str_final);
	}
	size = ft_find_good_size(var, &list, size);
	str_final = ft_strnewspace(size);
	str_final = ft_filling(str_final, var, &list);
	ft_free_float(&list, str, var);
	return (str_final);
}

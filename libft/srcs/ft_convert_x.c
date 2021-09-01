/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:35:04 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:09:10 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_put_hexa(char *var_hexa, t_option **list, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (var_hexa[0] == '0' && var_hexa[1] == '\0' && (*list)->prec == -1)
		return (str);
	if ((*list)->minus)
	{
		if ((*list)->hash && var_hexa[0] != '0')
			i += 2;
		while (str[i] != ' ')
			i++;
		while (var_hexa[j])
			str[i++] = var_hexa[j++];
		return (str);
	}
	else
	{
		i = ft_strlen(str) - ft_strlen(var_hexa);
		while (var_hexa[j])
			str[i++] = var_hexa[j++];
	}
	return (str);
}

static char	*ft_filling(char *str, char *var_hexa, t_option **list)
{
	size_t	len_var;
	int		nb_null;

	nb_null = 0;
	if (var_hexa[0] == '0' && var_hexa[1] == '\0')
		nb_null++;
	len_var = ft_strlen(var_hexa);
	if (nb_null && (((*list)->prec) > (int)len_var || (*list)->zero))
		str = ft_filling_zero_neg(str, list);
	else
	{
		if ((*list)->minus && (((*list)->zero) ||
					((*list)->prec > (int)len_var)))
			str = ft_put_zero_minus(str, var_hexa, list);
		else if (((*list)->zero && !(*list)->minus) ||
				((*list)->prec > (int)len_var))
			str = ft_put_zero(str, var_hexa, list);
	}
	if ((*list)->hash && !nb_null)
		str = ft_put_hash_x(str, var_hexa, list);
	str = ft_put_hexa(var_hexa, list, str);
	return (str);
}

static char	*ft_malloc_good_size(char *var_hexa, t_option **list, int nb_null)
{
	int		size_malloc;
	char	*str_final;
	size_t	len_var;

	len_var = ft_strlen(var_hexa);
	str_final = NULL;
	if ((*list)->hash && !nb_null)
		len_var += 2;
	if (len_var == 1 && !(*list)->min && !(*list)->prec)
		size_malloc = len_var;
	else if (len_var > (*list)->min && (int)len_var - 2 > (*list)->prec)
		size_malloc = len_var;
	else if ((*list)->min > len_var && (int)(*list)->min > (*list)->prec)
		size_malloc = (*list)->min;
	else if ((*list)->prec > (int)len_var - 2)
	{
		size_malloc = (*list)->prec;
		if ((*list)->hash && !nb_null)
			size_malloc += 2;
	}
	else
		size_malloc = len_var;
	str_final = ft_strnewspace(size_malloc);
	return (str_final);
}

static char	*ft_get_good_size(va_list ap, t_option **list, char *var, char *str)
{
	if (str[ft_strlen(str) - 1] == 'x')
		var = ft_get_good_size_unsigned(ap, list, 16);
	else if (str[ft_strlen(str) - 1] == 'X')
		var = ft_get_size_unsigned_big(ap, list, 16);
	return (var);
}

char		*ft_convert_x(va_list ap, char *str)
{
	t_option	*list;
	char		*var_hexa;
	int			nb_null;

	var_hexa = NULL;
	nb_null = 0;
	list = ft_get_option(str);
	var_hexa = ft_get_good_size(ap, &list, var_hexa, str);
	if (var_hexa[0] == '0' && var_hexa[1] == '\0' && list->prec == -1
			&& list->min == 0)
		return (ft_return_null_x(&list, str, var_hexa));
	if (str[1] == 'x' || str[1] == 'X')
	{
		ft_strdel(&str);
		ft_free_option(&list);
		return (var_hexa);
	}
	ft_strdel(&str);
	if (var_hexa[0] == '0' && var_hexa[1] == '\0')
		nb_null++;
	str = ft_malloc_good_size(var_hexa, &list, nb_null);
	str = ft_filling(str, var_hexa, &list);
	ft_free_option(&list);
	ft_strdel(&var_hexa);
	return (str);
}

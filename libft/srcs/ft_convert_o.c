/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_o.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:33:12 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:05:48 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_put_null(char *str, t_option **list)
{
	int		i;

	i = 0;
	if ((*list)->hash)
	{
		if ((*list)->minus)
			str[i] = '0';
		else
			str[ft_strlen(str) - 1] = '0';
	}
	return (str);
}

static char	*ft_put_octal(char *var_octal, t_option **list, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (var_octal[0] == '0' && var_octal[1] == '\0' && (*list)->prec == -1)
		return (str);
	if ((*list)->minus)
	{
		if ((*list)->hash)
			str[i++] = '0';
		while (str[i] != ' ')
			i++;
	}
	else
	{
		i = ft_strlen(str) - ft_strlen(var_octal);
		if ((*list)->hash && i - 1 >= 0)
			str[i - 1] = '0';
	}
	while (var_octal[j])
		str[i++] = var_octal[j++];
	return (str);
}

static char	*ft_malloc_good_size(char *var_octal, t_option **list)
{
	int		size_malloc;
	char	*str_final;
	size_t	len_var;

	len_var = ft_strlen(var_octal);
	str_final = NULL;
	if ((*list)->hash && var_octal[0] != '0')
		len_var++;
	if (len_var > (*list)->min && (int)len_var > (*list)->prec)
		size_malloc = len_var;
	else if ((*list)->min > len_var && (int)(*list)->min > (*list)->prec)
		size_malloc = (*list)->min;
	else if ((*list)->prec > (int)len_var || (*list)->prec > (int)(*list)->min)
		size_malloc = (*list)->prec;
	else
		size_malloc = len_var;
	str_final = ft_strnewspace(size_malloc);
	return (str_final);
}

static char	*ft_filling(char *str, char *var_octal, t_option **list)
{
	size_t	len_var;

	len_var = ft_strlen(var_octal);
	if ((*list)->hash && var_octal[0] != '0')
		len_var++;
	if ((*list)->minus && ((*list)->zero || ((*list)->prec > (int)len_var)))
		str = ft_put_zero_minus(str, var_octal, list);
	else if (((*list)->zero && !(*list)->minus) ||
			((*list)->prec > (int)len_var))
		str = ft_put_zero(str, var_octal, list);
	if (var_octal[0] == '0' && var_octal[1] == '\0' && (*list)->prec == -1)
		str = ft_put_null(str, list);
	else
		str = ft_put_octal(var_octal, list, str);
	return (str);
}

char		*ft_convert_o(va_list ap, char *str)
{
	t_option		*list;
	char			*var_octal;

	list = ft_get_option(str);
	var_octal = ft_get_good_size_unsigned(ap, &list, 8);
	if (str[1] == 'o')
	{
		ft_strdel(&str);
		ft_free_option(&list);
		return (var_octal);
	}
	ft_strdel(&str);
	if (var_octal[0] == '0' && var_octal[1] == '\0' && list->prec == -1 &&
			list->min == 0 && !list->hash)
	{
		ft_strdel(&var_octal);
		ft_free_option(&list);
		return (ft_strdup(""));
	}
	str = ft_malloc_good_size(var_octal, &list);
	str = ft_filling(str, var_octal, &list);
	ft_strdel(&var_octal);
	ft_free_option(&list);
	ft_strdel(&var_octal);
	return (str);
}

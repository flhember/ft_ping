/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:34:49 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:09:25 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_put_var(char *var, t_option **list, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (var[0] == '0' && var[1] == '\0' && (*list)->prec == -1)
		return (str);
	if ((*list)->minus)
	{
		while (str[i] != ' ')
			i++;
	}
	else
		i = ft_strlen(str) - ft_strlen(var);
	while (var[j])
		str[i++] = var[j++];
	return (str);
}

static char	*ft_malloc_good_size(char *var, t_option **list)
{
	int		size_malloc;
	char	*str_final;
	size_t	len_var;

	len_var = ft_strlen(var);
	str_final = NULL;
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

static char	*ft_filling(char *str, char *var, t_option **list)
{
	size_t	len_var;

	len_var = ft_strlen(var);
	if ((*list)->minus && ((*list)->zero || ((*list)->prec > (int)len_var)))
		str = ft_put_zero_minus(str, var, list);
	else if (((*list)->zero && !(*list)->minus) ||
			((*list)->prec > (int)len_var))
		str = ft_put_zero(str, var, list);
	str = ft_put_var(var, list, str);
	return (str);
}

char		*ft_convert_u(va_list ap, char *str)
{
	t_option		*list;
	char			*var;

	list = ft_get_option(str);
	var = ft_get_good_size_unsigned(ap, &list, 10);
	if (str[1] == 'u')
	{
		ft_free_option(&list);
		ft_strdel(&str);
		return (var);
	}
	ft_strdel(&str);
	if (var[0] == '0' && var[1] == '\0' && list->prec == -1 &&
			list->min == 0)
	{
		ft_free_option(&list);
		return (ft_strdup(""));
	}
	str = ft_malloc_good_size(var, &list);
	str = ft_filling(str, var, &list);
	ft_free_option(&list);
	ft_strdel(&var);
	return (str);
}

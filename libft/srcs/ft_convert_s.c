/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:49:07 by flhember          #+#    #+#             */
/*   Updated: 2019/05/01 16:35:48 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_filling(char *var, t_option **list, char *str)
{
	size_t	i;
	int		j;

	j = 0;
	i = 0;
	if ((*list)->minus)
	{
		while (var[j])
			str[i++] = var[j++];
		return (str);
	}
	i = ft_strlen(str) - ft_strlen(var);
	while (str[i])
		str[i++] = var[j++];
	if ((*list)->zero)
	{
		i = 0;
		while (str[i] == ' ')
			str[i++] = '0';
	}
	return (str);
}

static char	*ft_filling_prec(char *var, t_option **list, char *str)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	if ((*list)->minus)
	{
		while (j < (*list)->prec)
			str[i++] = var[j++];
		return (str);
	}
	i = ft_strlen(str) - (*list)->prec;
	while (str[i])
		str[i++] = var[j++];
	return (str);
}

static char	*ft_width_min(char *var, t_option **list)
{
	char	*tmp;

	tmp = NULL;
	if ((*list)->prec == -1)
		return (tmp = ft_strdup(""));
	else if ((*list)->min > ft_strlen(var))
		tmp = ft_strnewspace((*list)->min);
	else if ((*list)->prec != 0 && (*list)->prec < (int)ft_strlen(var)
			&& (int)(*list)->min < (*list)->prec)
		tmp = ft_strnewspace((*list)->prec);
	else if ((*list)->prec != 0 && (*list)->prec < (int)ft_strlen(var)
			&& (int)(*list)->min >= (*list)->prec)
		tmp = ft_strnewspace((*list)->min);
	else
		tmp = ft_strnewspace(ft_strlen(var));
	if ((*list)->prec != 0 && (*list)->prec < (int)ft_strlen(var))
		return (ft_filling_prec(var, list, tmp));
	return (ft_filling(var, list, tmp));
}

char		*ft_convert_s(va_list ap, char *str)
{
	t_option	*list;
	char		*tmp;
	int			flag;

	flag = 1;
	tmp = va_arg(ap, char*);
	list = NULL;
	if (tmp == NULL)
	{
		tmp = ft_strdup("(null)");
		flag = 0;
	}
	if (str[1] == 's')
	{
		ft_strdel(&str);
		str = ft_strdup(tmp);
		flag == 0 ? ft_strdel(&tmp) : tmp;
		return (str);
	}
	list = ft_get_option(str);
	ft_strdel(&str);
	str = ft_width_min(tmp, &list);
	ft_free_option(&list);
	flag == 0 ? ft_strdel(&tmp) : tmp;
	return (str);
}

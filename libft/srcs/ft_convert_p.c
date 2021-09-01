/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:59:31 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:02:17 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_filling(char *adr, t_option **list, char *tmp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((*list)->minus)
	{
		while (adr[j])
			tmp[i++] = adr[j++];
		return (tmp);
	}
	else
	{
		i = ft_strlen(tmp) - ft_strlen(adr);
		while (adr[j])
			tmp[i++] = adr[j++];
	}
	return (tmp);
}

static char	*ft_width_min(char *adr, t_option **list)
{
	char	*tmp;

	tmp = NULL;
	if ((*list)->min <= ft_strlen(adr))
		return (adr);
	tmp = ft_strnewspace((*list)->min);
	tmp = ft_filling(adr, list, tmp);
	ft_strdel(&adr);
	return (tmp);
}

static char	*ft_convert_hexa(unsigned long adr)
{
	char	*final;
	char	*res;

	final = NULL;
	res = ft_ultoa_base(adr, 16);
	final = ft_strjoinfree("0x", res, 2);
	return (final);
}

char		*ft_convert_p(va_list ap, char *str)
{
	unsigned long		adr;
	t_option			*list;

	list = NULL;
	adr = va_arg(ap, unsigned long);
	if (str[1] == 'p')
	{
		ft_strdel(&str);
		str = ft_convert_hexa(adr);
		return (str);
	}
	list = ft_get_option(str);
	ft_strdel(&str);
	str = ft_width_min(ft_convert_hexa(adr), &list);
	ft_free_option(&list);
	return (str);
}

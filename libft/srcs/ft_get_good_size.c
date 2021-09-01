/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_good_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:03:59 by flhember          #+#    #+#             */
/*   Updated: 2019/05/01 11:55:13 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_get_size_unsigned_big(va_list ap, t_option **list, int base)
{
	if (!(*list)->size)
		return (ft_ultoa_base_big(va_arg(ap, unsigned int), base));
	else if ((*list)->size[0] == 'l')
	{
		if ((*list)->size[1] == 'l')
			return (ft_ultoa_base_big(va_arg(ap, unsigned long long), base));
		else
			return (ft_ultoa_base_big(va_arg(ap, unsigned long), base));
	}
	else if ((*list)->size[0] == 'h')
	{
		if ((*list)->size[1] == 'h')
			return (ft_ultoa_base_big((unsigned char)(va_arg(ap, unsigned int))
						, base));
		else
			return (ft_ultoa_base_big((unsigned short)(va_arg(ap, unsigned int))
						, base));
	}
	return (0);
}

char	*ft_get_good_size_unsigned(va_list ap, t_option **list, int base)
{
	if (!(*list)->size)
		return (ft_ultoa_base(va_arg(ap, unsigned int), base));
	else if ((*list)->size[0] == 'l')
	{
		if ((*list)->size[1] == 'l')
			return (ft_ultoa_base(va_arg(ap, unsigned long long), base));
		else
			return (ft_ultoa_base(va_arg(ap, unsigned long), base));
	}
	else if ((*list)->size[0] == 'h')
	{
		if ((*list)->size[1] == 'h')
			return (ft_ultoa_base((char)(va_arg(ap, unsigned int)), base));
		else
			return (ft_ultoa_base((short)(va_arg(ap, unsigned int)), base));
	}
	return (0);
}

char	*ft_get_good_size_signed(va_list ap, t_option **list)
{
	if (!(*list)->size)
		return (ft_itoa(va_arg(ap, int)));
	else if ((*list)->size[0] == 'l')
	{
		if ((*list)->size[1] == 'l')
			return (ft_lltoa(va_arg(ap, long long)));
		else
			return (ft_lltoa(va_arg(ap, long)));
	}
	else if ((*list)->size[0] == 'h')
	{
		if ((*list)->size[1] == 'h')
			return (ft_lltoa((char)(va_arg(ap, int))));
		else
			return (ft_lltoa((short)(va_arg(ap, int))));
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_flag_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 12:09:39 by flhember          #+#    #+#             */
/*   Updated: 2019/05/01 12:39:30 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		ft_put_flag_size(char *str, int i, t_option **list)
{
	if ((str[i - 1] == 'l' || str[i + 1] == 'l') && str[i++])
	{
		if ((*list)->size)
			ft_strdel(&(*list)->size);
		(*list)->size = ft_strdup("ll");
	}
	else if ((str[i - 1] == 'h' || str[i + 1] == 'h') && str[i++])
	{
		if ((*list)->size)
			ft_strdel(&(*list)->size);
		(*list)->size = ft_strdup("hh");
	}
	else
		(*list)->size = ft_strsub(str, i, 1);
}

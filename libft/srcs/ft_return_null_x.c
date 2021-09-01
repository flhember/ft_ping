/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_null_x.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:26:31 by flhember          #+#    #+#             */
/*   Updated: 2019/05/01 12:38:47 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_return_null_x(t_option **list, char *str, char *var_hexa)
{
	ft_free_option(list);
	ft_strdel(&str);
	ft_strdel(&var_hexa);
	return (ft_strdup(""));
}

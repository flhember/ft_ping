/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:16:32 by flhember          #+#    #+#             */
/*   Updated: 2019/05/02 16:53:51 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_set_list(t_option **list)
{
	(*list)->min = 0;
	(*list)->prec = 0;
	(*list)->plus = 0;
	(*list)->minus = 0;
	(*list)->hash = 0;
	(*list)->space = 0;
	(*list)->zero = 0;
	(*list)->size = NULL;
	(*list)->option = NULL;
}

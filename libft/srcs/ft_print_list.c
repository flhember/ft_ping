/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 20:22:24 by flhember          #+#    #+#             */
/*   Updated: 2019/01/24 16:00:26 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_list(t_list *list)
{
	while (list)
	{
		ft_putstr("[\n");
		ft_putstr((char*)(list->content));
		ft_putstr("\n]");
		ft_putstr(" size: ");
		ft_putnbr((int)(list->content_size));
		ft_putstr("  -->  ");
		list = list->next;
	}
	ft_putstr("NULL\n");
}

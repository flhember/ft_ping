/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creatlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:12:25 by flhember          #+#    #+#             */
/*   Updated: 2019/05/02 17:25:20 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_conv	*ft_creat_maillon(char c, char *(*ft)(va_list ap, char *str))
{
	t_conv	*new;

	new = NULL;
	if (!(new = (t_conv*)malloc(sizeof(t_conv))))
		return (NULL);
	new->type = c;
	new->f = ft;
	new->next = NULL;
	return (new);
}

static void		ft_add_maillon(t_conv **list, t_conv *new)
{
	new->next = *list;
	*list = new;
}

void			ft_createndlst(t_conv **list)
{
	t_conv	*tmp;

	tmp = ft_creat_maillon('%', &ft_convert_percent);
	ft_add_maillon(list, tmp);
}

void			ft_creatlst(t_conv **list)
{
	t_conv	*tmp;

	tmp = ft_creat_maillon('c', &ft_convert_c);
	ft_add_maillon(list, tmp);
	tmp = ft_creat_maillon('s', &ft_convert_s);
	ft_add_maillon(list, tmp);
	tmp = ft_creat_maillon('p', &ft_convert_p);
	ft_add_maillon(list, tmp);
	tmp = ft_creat_maillon('i', &ft_convert_i_d);
	ft_add_maillon(list, tmp);
	tmp = ft_creat_maillon('d', &ft_convert_i_d);
	ft_add_maillon(list, tmp);
	tmp = ft_creat_maillon('o', &ft_convert_o);
	ft_add_maillon(list, tmp);
	tmp = ft_creat_maillon('x', &ft_convert_x);
	ft_add_maillon(list, tmp);
	tmp = ft_creat_maillon('X', &ft_convert_x);
	ft_add_maillon(list, tmp);
	tmp = ft_creat_maillon('u', &ft_convert_u);
	ft_add_maillon(list, tmp);
	tmp = ft_creat_maillon('f', &ft_convert_f);
	ft_add_maillon(list, tmp);
	tmp = ft_creat_maillon('b', &ft_convert_b);
	ft_add_maillon(list, tmp);
	ft_createndlst(list);
}

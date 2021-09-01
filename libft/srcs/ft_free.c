/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 11:56:15 by brpinto           #+#    #+#             */
/*   Updated: 2019/11/12 14:40:37 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_free_ftoa(t_ftoa **list)
{
	if ((*list)->expo)
		ft_strdel(&(*list)->expo);
	if ((*list)->mant)
		ft_strdel(&(*list)->mant);
	free(*list);
}

void	ft_free_option(t_option **list)
{
	if ((*list)->size)
		ft_strdel(&(*list)->size);
	free(*list);
}

void	ft_free_tab(char **tab)
{
	int		j;

	j = 0;
	while (tab[j])
	{
		ft_strdel(&tab[j]);
		j++;
	}
	free(tab);
}

void	ft_free_list(t_conv **list)
{
	if ((*list)->next)
		ft_free_list(&(*list)->next);
	free(*list);
}

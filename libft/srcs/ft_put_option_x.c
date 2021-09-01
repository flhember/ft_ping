/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_option_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:06:30 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:15:22 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_put_hash_x(char *str, char *var, t_option **list)
{
	size_t	i;

	i = 0;
	if (!(*list)->minus)
	{
		while (str[i] == ' ' && i < ft_strlen(str) - ft_strlen(var))
			i++;
		if ((*list)->flag == 'x')
			str[--i] = 'x';
		else
			str[--i] = 'X';
		str[--i] = '0';
	}
	else
	{
		str[i] = '0';
		if ((*list)->flag == 'x')
			str[++i] = 'x';
		else
			str[++i] = 'X';
	}
	return (str);
}

char	*ft_filling_zero_neg(char *str, t_option **list)
{
	int		i;
	int		j;

	j = 0;
	if ((*list)->minus)
	{
		while (j++ < (*list)->prec - 1)
			str[j] = '0';
	}
	else if (!(*list)->prec)
	{
		i = (int)ft_strlen(str) - 1;
		while (i >= j)
			str[i--] = '0';
	}
	else
	{
		i = (int)ft_strlen(str) - 1;
		while (j++ < (*list)->prec)
			str[i--] = '0';
	}
	return (str);
}

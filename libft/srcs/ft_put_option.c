/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_option.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:36:13 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:14:48 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char		*ft_put_zero_minus(char *str, char *var, t_option **list)
{
	int		i;
	size_t	size_var;
	int		j;

	j = 0;
	size_var = ft_strlen(var) + 1;
	i = 0;
	if ((var[0] != '-' && ((*list)->plus || (*list)->space)) || (var[0] == '-'))
	{
		i++;
		if (var[0] == '-')
			size_var--;
	}
	if ((*list)->hash && ((*list)->flag == 'x' || (*list)->flag == 'X'))
		i += 2;
	while (j++ <= (int)(*list)->prec - (int)size_var)
		str[i++] = '0';
	return (str);
}

char		*ft_put_zero(char *str, char *var, t_option **list)
{
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(str) - ft_strlen(var);
	if (var[0] != '-')
		i--;
	if ((*list)->plus || (*list)->space || var[0] == '-')
		j++;
	if (!(*list)->prec)
	{
		if ((*list)->hash && ((*list)->flag == 'x' || (*list)->flag == 'X'))
			j += 2;
		while (i >= j)
			str[i--] = '0';
	}
	else
	{
		j = ft_strlen(var);
		if (var[0] == '-')
			j--;
		while (j++ < (int)(*list)->prec)
			str[i--] = '0';
	}
	return (str);
}

char		*ft_put_signe(char *str, char *var, t_option **list, size_t size)
{
	int		i;

	if ((*list)->minus || ((*list)->zero && !(*list)->prec))
		i = 0;
	else if ((ft_strlen(var) > (*list)->min && (*list)->min > 0) ||
				(((int)ft_strlen(var) > (*list)->prec && (*list)->prec > 0)
					&& !(*list)->min))
		i = 0;
	else if (((*list)->min <= ft_strlen(var)))
		i = 0;
	else if (!(*list)->prec || (*list)->prec <= (int)size)
	{
		i = (*list)->min - ft_strlen(var);
		if (var[0] != '-')
			i -= 1;
	}
	else
		i = ft_strlen(str) - (*list)->prec - 1;
	if (var[0] == '-')
		str[i] = '-';
	else if ((*list)->plus)
		str[i] = '+';
	return (str);
}

char		*ft_put_num(char *str, char *var, t_option **list, size_t size)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (var[0] == '0' && var[1] == '\0' && (*list)->prec == -1)
		return (str);
	if (var[0] == '-' || var[0] == '+')
		j++;
	if (!(*list)->minus)
		i = ft_strlen(str) - size;
	else
	{
		if ((*list)->space)
			i++;
		while (str[i] != ' ')
			i++;
	}
	while (var[j])
		str[i++] = var[j++];
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_option.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:37:40 by flhember          #+#    #+#             */
/*   Updated: 2019/05/01 12:27:48 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_get_size_option(t_option **list, char *str, size_t i)
{
	while (str[i])
	{
		if (str[i] == 'l' || str[i] == 'h' || str[i] == 'L')
		{
			ft_put_flag_size(str, i, list);
			i++;
		}
		else if (str[i] == ' ' || str[i] == '-' || str[i] == '#' ||
				str[i] == '+' || ((str[i] == '0' && str[i - 1] < '0' &&
					str[i - 1] != '.') || (str[i] == '0' && str[i - 1] > '9'
						&& str[i - 1] != '.')))
		{
			if (!(*list)->option)
				(*list)->option = ft_strsub(str, i, 1);
			else
				(*list)->option =
					ft_strjoinfree((*list)->option, ft_strsub(str, i, 1), 3);
			i++;
		}
		else
			i++;
	}
}

static void	ft_get_min_prec(t_option **list, char *str, size_t i)
{
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9' && str[i - 1] != '.')
		{
			(*list)->min = ft_atoi(str + i);
			while (str[i] >= '0' && str[i] <= '9')
				i++;
		}
		else if (str[i] == '.' && (str[i + 1] < '0' || str[i + 1] > '9'))
		{
			(*list)->prec = -1;
			i++;
		}
		else if (str[i] >= '0' && str[i] <= '9' && str[i - 1] == '.')
		{
			(*list)->prec = ft_atoi(str + i);
			if ((*list)->prec == 0)
				(*list)->prec = -1;
			while (str[i] >= '0' && str[i] <= '9')
				i++;
		}
		else
			i++;
	}
}

static void	ft_get_good_option(t_option **list, int j)
{
	int		i;

	i = 0;
	while ((*list)->option[i])
	{
		if ((*list)->option[i] == '+')
		{
			while ((*list)->option[j++])
			{
				if ((*list)->option[j] == ' ')
					(*list)->option[j] = '.';
			}
			j = 0;
		}
		else if ((*list)->option[i] == '-')
		{
			while ((*list)->option[j++])
			{
				if ((*list)->option[j] == '0')
					(*list)->option[j] = '.';
			}
			j = 0;
		}
		i++;
	}
}

static void	ft_put_option(t_option **list)
{
	int		i;

	i = 0;
	while ((*list)->option[i])
	{
		if ((*list)->option[i] == '-')
			(*list)->minus++;
		if ((*list)->option[i] == '+')
			(*list)->plus++;
		if ((*list)->option[i] == ' ')
			(*list)->space++;
		if ((*list)->option[i] == '0')
			(*list)->zero++;
		if ((*list)->option[i] == '#')
			(*list)->hash++;
		i++;
	}
	free((*list)->option);
}

t_option	*ft_get_option(char *str)
{
	t_option	*list;
	size_t		i;
	int			j;

	j = 0;
	i = 1;
	list = NULL;
	if (!(list = (t_option*)malloc(sizeof(t_option))))
		return (NULL);
	ft_set_list(&list);
	list->flag = str[(ft_strlen(str) - 1)];
	if (ft_strlen(str) > 2)
	{
		ft_get_min_prec(&list, str, i);
		ft_get_size_option(&list, str, i);
		if (list->option)
		{
			ft_get_good_option(&list, j);
			ft_put_option(&list);
		}
	}
	return (list);
}

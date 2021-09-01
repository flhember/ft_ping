/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:38:06 by flhember          #+#    #+#             */
/*   Updated: 2019/05/06 16:28:14 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char		*ft_check_hash(char *str, int hash)
{
	char	*str_final;

	str_final = NULL;
	if (str[ft_strlen(str) - 1] == '.')
	{
		if (!hash)
		{
			str_final = ft_strsub(str, 0, (ft_strlen(str) - 1));
			ft_strdel(&str);
			return (str_final);
		}
	}
	return (str);
}

char		*ft_good_var(va_list ap, t_option **list)
{
	char	*str;

	str = NULL;
	if (!((*list)->size) || (*list)->size[0] == 'l')
	{
		if ((*list)->prec == 0)
			str = ft_ftoa_dbl(va_arg(ap, double), 6, (*list)->hash);
		else if ((*list)->prec == -1)
			str = ft_ftoa_dbl(va_arg(ap, double), 0, (*list)->hash);
		else
			str = ft_ftoa_dbl(va_arg(ap, double), (*list)->prec, (*list)->hash);
	}
	else if ((*list)->size[0] == 'L')
	{
		if ((*list)->prec == 0)
			str = ft_ftoa_ldbl(va_arg(ap, long double), 6, (*list)->hash);
		else if ((*list)->prec == -1)
			str = ft_ftoa_ldbl(va_arg(ap, long double), 0, (*list)->hash);
		else
			str = ft_ftoa_ldbl(va_arg(ap, long double),
					(*list)->prec, (*list)->hash);
	}
	return (str);
}

void		ft_free_float(t_option **list, char *str, char *var)
{
	ft_free_option(list);
	ft_strdel(&str);
	ft_strdel(&var);
}

void		ft_verif_size(char **s1, char **s2)
{
	int		i;
	int		j;

	i = ft_strlen((*s1));
	j = ft_strlen((*s2));
	if (i < j)
		while (i++ < j)
			*s1 = ft_strjoinfree("0", *s1, 2);
	else if (j < i)
		while (j++ < i)
			*s2 = ft_strjoinfree("0", *s2, 2);
}

char		*ft_get_round_after(char *str, int i)
{
	if (str[i] >= '5' && str[i] <= '9')
	{
		if (str[i - 1] == '.')
			i--;
		if (str[i - 1] != '9')
			str[i - 1] = str[i - 1] + 1;
		else
		{
			while (str[i - 1] == '9')
			{
				str[i - 1] = '0';
				i--;
				if (str[i - 1] == '.')
					i--;
			}
			str[i - 1] += 1;
			if (str[0] == '0' && i == 0)
				str = ft_strjoinfree("1", str, 2);
		}
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_float1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:30:23 by flhember          #+#    #+#             */
/*   Updated: 2019/10/28 11:26:32 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int			ft_size_vir(long double f)
{
	int		i;

	i = 1;
	while (f >= 10 || f <= -10)
	{
		f /= 10;
		i++;
	}
	return (i);
}

char		*ft_nan_inf(t_ftoa **list)
{
	char	*str;
	size_t	i;

	i = 0;
	str = NULL;
	while ((*list)->expo[i] == '1')
		i++;
	if (i == ft_strlen((*list)->expo))
	{
		i = 0;
		if ((*list)->signe == 0)
			str = ft_strdup("inf");
		else if ((*list)->signe == 1)
			str = ft_strdup("-inf");
		while ((*list)->mant[i] == '0')
			i++;
		if (i < ft_strlen((*list)->mant) - 1)
		{
			ft_strdel(&str);
			str = ft_strdup("nan");
		}
	}
	if (str)
		ft_free_ftoa(list);
	return (str);
}

char		*ft_zero_prec(char *str, int i)
{
	char	*str_cpy;
	int		j;
	int		k;

	j = 0;
	k = ft_strlen(str) - 1;
	str_cpy = ft_strdup(str);
	while (str[j] != '.')
		j++;
	k -= j;
	while (k++ < i)
		str_cpy = ft_strjoinfree(str_cpy, "0", 1);
	ft_strdel(&str);
	return (str_cpy);
}

char		*ft_put_point(char *str, int vir)
{
	int		i;
	char	*end;
	char	*start;
	char	*str_final;

	end = NULL;
	start = NULL;
	str_final = NULL;
	i = ft_strlen(str) - vir;
	start = ft_strsub(str, 0, vir);
	end = ft_strsub(str, vir, i);
	str_final = ft_strjoinfree(start, ".", 1);
	str_final = ft_strjoinfree(str_final, end, 3);
	ft_strdel(&str);
	return (str_final);
}

char		*ft_ld_in_str(long double res, int i)
{
	char	*str;
	int		j;

	j = 0;
	if (!(str = (char*)ft_memalloc(sizeof(char) * 1000)))
		return (NULL);
	if (i == 1)
		str[j++] = (int)res + 49;
	else if (i == 0)
		str[j++] = (int)res + 48;
	if ((int)res > 0)
		res = (res - (int)res);
	while (res && j < 200)
	{
		res *= 10.00;
		str[j++] = (int)res + 48;
		res -= (int)res;
	}
	return (str);
}

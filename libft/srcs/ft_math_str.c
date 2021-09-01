/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:02:54 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:16:37 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char		*ft_add_str_bis(char *s1, char *s2, char *res, int retenu)
{
	int		i;
	int		tmp;
	int		k;

	k = 0;
	i = ft_strlen(s1);
	while (--i >= 0)
	{
		tmp = (s1[i] - 48) + (s2[i] - 48) + retenu;
		if (tmp > 9)
		{
			retenu = tmp / 10;
			tmp = tmp % 10;
		}
		else
			retenu = 0;
		res[k++] = (char)tmp + 48;
	}
	if (retenu)
		res[k++] = (char)retenu + 48;
	return (res);
}

char		*ft_add_str(char *s1, char *s2)
{
	char	*res;
	int		retenu;

	retenu = 0;
	ft_verif_size(&s1, &s2);
	if (!(res = (char*)ft_memalloc(sizeof(char) * (5000))))
		return (NULL);
	res = ft_add_str_bis(s1, s2, res, retenu);
	ft_strdel(&s1);
	res = ft_str_rev(res);
	return (res);
}

char		*ft_mult(char *str_fl, int div, int k)
{
	int		j;
	int		tmp;
	int		retenu;
	char	*res;

	k = 0;
	retenu = 0;
	j = ft_strlen(str_fl) - 1;
	if (!(res = (char*)ft_memalloc(sizeof(char) * (5000))))
		return (NULL);
	while (j >= 0)
	{
		tmp = div * ((int)str_fl[j--] - 48) + retenu;
		if (tmp > 9)
		{
			retenu = tmp / 10;
			tmp = tmp % 10;
		}
		else
			retenu = 0;
		res[k++] = (char)tmp + 48;
	}
	if (retenu)
		res[k++] = retenu + 48;
	return (res);
}

char		*ft_mult_str(char *str_fl, char *str_en)
{
	char	*str_final;
	char	*res;
	int		j;
	int		i;
	int		div;

	i = -1;
	str_final = NULL;
	res = NULL;
	while (++i < (int)ft_strlen(str_en))
	{
		div = (int)str_en[ft_strlen(str_en) - i - 1] - 48;
		res = ft_mult(str_fl, div, i);
		j = 0;
		while (j++ < i)
			res = ft_strjoinfree("0", res, 2);
		res = ft_str_rev(res);
		if (!str_final)
			str_final = ft_strdup(res);
		else
			str_final = ft_add_str(str_final, res);
		ft_strdel(&res);
	}
	return (str_final);
}

char		*ft_pow_to_str(long b)
{
	int		i;
	char	*tmp;
	char	*str;

	i = 1;
	tmp = ft_strdup("2");
	str = NULL;
	while (i++ < b)
	{
		str = ft_mult_str(tmp, "2");
		ft_strdel(&tmp);
		tmp = ft_strdup(str);
		ft_strdel(&str);
	}
	return (tmp);
}

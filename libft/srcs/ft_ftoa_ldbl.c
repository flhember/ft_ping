/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_80.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:26:50 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:16:00 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <math.h>
#include <float.h>

static char		*ft_get_expo_80(t_ftoa **list)
{
	int			i;
	int			j;
	long double	tmp;
	char		*exp;

	i = 15;
	j = 0;
	tmp = 0;
	while (--i >= 0)
	{
		if ((*list)->expo[i] == '1')
			tmp += ft_pow(2, j);
		j++;
	}
	tmp -= 16383;
	if (tmp <= 0)
	{
		tmp = ft_pow(2, tmp);
		exp = ft_ld_in_str(tmp, 0);
	}
	else
		exp = ft_pow_to_str((long)tmp);
	ft_strdel(&(*list)->expo);
	return (exp);
}

static char		*ft_get_mant_80(t_ftoa **list)
{
	int			i;
	int			j;
	long double	tmp;
	char		*mant;

	i = 0;
	j = 0;
	tmp = 0;
	mant = NULL;
	while ((*list)->mant[i])
	{
		if ((*list)->mant[i] == '1')
			tmp += ft_pow(2, j);
		j--;
		i++;
	}
	mant = ft_ld_in_str(tmp, 0);
	ft_strdel(&(*list)->mant);
	return (mant);
}

static void		ft_set_list_ftoaldbl(t_ftoa **list, t_ftoa80 ieee)
{
	(*list)->mant = ft_ultoa_base(ieee.bin.mant1, 2);
	(*list)->expo = ft_ultoa_base(ieee.bin.expo, 2);
	(*list)->signe = ieee.bin.signe;
	while (ft_strlen((*list)->expo) != 15)
		(*list)->expo = ft_strjoinfree("0", (*list)->expo, 2);
	while (ft_strlen((*list)->mant) != 64)
		(*list)->mant = ft_strjoinfree("0", (*list)->mant, 2);
}

char			*ft_ftoa_ldbl(long double f, int prec, int hash)
{
	t_ftoa		*list;
	t_ftoa80	ieee;
	char		*str;
	int			vir;

	str = NULL;
	ieee.d = f;
	if (!(list = malloc(sizeof(t_ftoa))))
		return (NULL);
	ft_set_list_ftoaldbl(&list, ieee);
	if ((str = ft_nan_inf(&list)) != NULL)
		return (str);
	vir = ft_size_vir(f);
	list->mant = ft_get_mant_80(&list);
	list->expo = ft_get_expo_80(&list);
	str = ft_mult_str(list->mant, list->expo);
	str = ft_put_point(str, vir);
	if ((long)(ft_strlen(str) - vir) > prec)
		str = ft_cut_prec(str, prec, vir, hash);
	if (prec != 0 && prec != -1 && (long)(ft_strlen(str) - vir - 1) < prec)
		str = ft_zero_prec(str, prec);
	list->signe == 1 ? (str = ft_strjoinfree("-", str, 2)) : str;
	ft_free_ftoa(&list);
	return (str);
}

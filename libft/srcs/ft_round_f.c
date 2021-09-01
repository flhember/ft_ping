/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:47:19 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:15:34 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*ft_get_rond(char *str, int i)
{
	char	*str_final;

	i = ft_strlen(str) - 1;
	str_final = NULL;
	if (str[i] == '.')
		i--;
	str = ft_get_round_after(str, i);
	str_final = ft_strsub(str, 0, (ft_strlen(str) - 1));
	ft_strdel(&str);
	return (str_final);
}

static int		ft_round_or_not(char *str, int vir)
{
	int		i;
	int		rep;

	rep = 0;
	i = vir + 3;
	while (str[--i] != '.')
	{
		if (rep == 1)
		{
			if (str[i] == '9')
				return (1);
			else
				str[i] += 1;
		}
		if (str[i] >= '5' && str[i] <= '9')
			rep = 1;
	}
	if (str[i + 1] == '5')
		if (((int)(str[i - 1] - 48) % 2) != 0)
			return (1);
		else
			return (0);
	else if (str[i + 1] < '5' && str[i + 1] >= '0')
		rep = 0;
	return (rep);
}

static char		*ft_round_before_vir(char *str)
{
	char	*str_final;
	int		i;

	str_final = NULL;
	i = ft_strlen(str) - 1;
	if (i == 0 && str[i] == '9')
		str_final = ft_strdup("10");
	else
	{
		str_final = ft_strdup(str);
		if (str_final[i] != '9')
			str_final[i] += 1;
		else
		{
			while (str_final[i] == '9')
				str_final[i--] = '0';
			if (str_final[0] == '0' && (i == 0 || i == -1))
				str_final = ft_strjoinfree("1", str_final, 2);
			else
				str_final[i] += 1;
		}
	}
	ft_strdel(&str);
	return (str_final);
}

static char		*ft_get_rond_null(char *str, int hash, int vir)
{
	int		i;
	char	*str_final;

	i = 0;
	if (!(str_final = (char *)ft_memalloc(sizeof(char) * (vir + 1))))
		return (NULL);
	while (i < vir)
	{
		str_final[i] = str[i];
		i++;
	}
	if (ft_round_or_not(str, vir) == 1)
		str_final = ft_round_before_vir(str_final);
	if (hash)
		str_final = ft_strjoinfree(str_final, ".", 1);
	ft_strdel(&str);
	return (str_final);
}

char			*ft_cut_prec(char *str, int prec, int vir, int hash)
{
	char	*str_final;
	int		i;

	i = 0;
	str_final = NULL;
	if (prec == 0 || prec == -1)
		return (ft_get_rond_null(str, hash, vir));
	if (!(str_final = (char *)ft_memalloc(sizeof(char) * (prec + vir + 3))))
		return (NULL);
	while (str[i] && i < prec + vir + 2)
	{
		str_final[i] = str[i];
		i++;
	}
	if (prec + vir + 1 < ((int)ft_strlen(str) - 1))
		str_final = ft_get_rond(str_final, i);
	else if (prec + vir + 1 >= ((int)ft_strlen(str) - 1))
	{
		ft_strdel(&str_final);
		str_final = ft_strsub(str, 0, vir + prec + 1);
	}
	str_final = ft_check_hash(str_final, hash);
	ft_strdel(&str);
	return (str_final);
}

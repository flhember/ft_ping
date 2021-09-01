/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 19:33:24 by flhember          #+#    #+#             */
/*   Updated: 2019/03/05 14:56:53 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_get_size(long long n)
{
	int		size;

	size = 1;
	if (n < 0)
	{
		n = -n;
		size++;
	}
	while (n > 9)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static	char	*remplissage(char *str, long long n, long long cpyneg, int size)
{
	while (size >= 0)
	{
		str[size] = (n % 10) + 48;
		n = n / 10;
		size--;
	}
	if (cpyneg < 0)
		str[0] = '-';
	return (str);
}

char			*ft_lltoa(long long n)
{
	int			size;
	char		*str;
	long long	cpyneg;

	cpyneg = n;
	size = ft_get_size(n);
	if (n == LLONG_MIN)
	{
		str = ft_strdup("-9223372036854775808");
		return (str);
	}
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str[size] = '\0';
	size--;
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
		n = -n;
	str = remplissage(str, n, cpyneg, size);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 19:33:24 by flhember          #+#    #+#             */
/*   Updated: 2019/10/11 15:16:49 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		sizeint(int n)
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

static	char	*remplissage(char *str, int n, int cpyneg, int size)
{
	while (size >= 0)
	{
		str[size] = (n % 10) + '0';
		n = n / 10;
		size--;
	}
	if (cpyneg < 0)
		str[0] = '-';
	return (str);
}

char			*ft_itoa(int n)
{
	int		size;
	char	*str;
	int		cpyneg;

	cpyneg = n;
	size = sizeint(n);
	if (n == -2147483648)
	{
		str = ft_strdup("-2147483648");
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

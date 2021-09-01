/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultoa_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 02:32:33 by flhember          #+#    #+#             */
/*   Updated: 2019/04/29 12:53:46 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		ft_get_size(unsigned long n, int base)
{
	int		size;

	size = 1;
	while (n > (unsigned long)base - 1)
	{
		n = n / base;
		size++;
	}
	return (size);
}

char			*ft_ultoa_base(unsigned long n, int base)
{
	char			*ascii;
	char			*str;
	int				size;
	unsigned long	cpy;

	cpy = n;
	size = ft_get_size(cpy, base);
	ascii = "0123456789abcdef";
	if (base < 2 || base > 16)
		return (NULL);
	if (!(str = (char*)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (n || size > 0)
	{
		str[--size] = ascii[n % base];
		n /= base;
	}
	return (str);
}

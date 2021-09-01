/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:37:18 by flhember          #+#    #+#             */
/*   Updated: 2019/04/12 14:19:38 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double		ft_pow(long double a, long double b)
{
	long double	res;
	int			i;
	int			nega;
	int			negb;

	nega = 0;
	negb = 0;
	i = 1;
	res = a;
	if (b == 0)
		return (1);
	if (a < 0 && (++nega))
		a *= -1;
	if (b < 0 && (++negb))
		b *= -1;
	while (i++ < b)
		res = res * a;
	if (nega)
		if ((int)a % 2 != 0)
			res *= -1;
	if (negb)
		res = 1 / res;
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:17:20 by flhember          #+#    #+#             */
/*   Updated: 2019/01/24 15:59:58 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*destcpy;
	size_t	zero;

	zero = 0;
	if (dest > src)
	{
		while (n > zero)
		{
			((char*)dest)[n - 1] = ((char*)src)[n - 1];
			n--;
		}
		return (dest);
	}
	else
	{
		destcpy = ft_memcpy(dest, src, n);
		return (destcpy);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 15:30:37 by flhember          #+#    #+#             */
/*   Updated: 2019/01/24 16:01:25 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	sizedst;

	sizedst = ft_strlen(dst);
	if (size <= sizedst)
		return (ft_strlen(src) + size);
	else
	{
		ft_strncat(dst, src, size - sizedst - 1);
		return (ft_strlen(src) + sizedst);
	}
}

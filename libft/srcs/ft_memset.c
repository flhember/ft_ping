/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:37:46 by flhember          #+#    #+#             */
/*   Updated: 2019/01/24 16:00:11 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*cpy;

	cpy = s;
	i = 0;
	while (i < n)
	{
		cpy[i] = (unsigned char)c;
		i++;
	}
	return (cpy);
}

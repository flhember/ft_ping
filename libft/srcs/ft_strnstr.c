/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:17:45 by flhember          #+#    #+#             */
/*   Updated: 2019/12/03 14:50:15 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s2[0] == '\0')
		return ((char*)s1);
	while (s1[i] != '\0' && i < len)
	{
		while (s1[i + j] == s2[j] && i + j < len)
		{
			j++;
			if (s2[j] == '\0')
				return ((char*)(s1 + i));
		}
		j = 0;
		i++;
	}
	return (0);
}

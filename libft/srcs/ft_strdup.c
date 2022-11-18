/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:24:20 by flhember          #+#    #+#             */
/*   Updated: 2019/05/08 12:44:22 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		size;

	size = 0;
	dest = NULL;
	while (s[size] != '\0')
		size++;
	if (!(dest = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	size = 0;
	while (s[size] != '\0')
	{
		dest[size] = s[size];
		size++;
	}
	dest[size] = '\0';
	return (dest);
}

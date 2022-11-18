/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:28:50 by flhember          #+#    #+#             */
/*   Updated: 2020/01/15 16:29:22 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncut(char *str, int n)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!(new_str = ft_memalloc(sizeof(char) * (n + 1))))
		return (NULL);
	while (i < n)
	{
		new_str[i] = str[i];
		i++;
	}
	return (new_str);
}

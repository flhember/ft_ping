/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_rev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 12:41:27 by flhember          #+#    #+#             */
/*   Updated: 2019/04/18 13:05:42 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_rev(char *str)
{
	int		i;
	int		j;
	char	*cpy;

	i = 0;
	j = ft_strlen(str) - 1;
	if (!(cpy = (char*)ft_memalloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (i <= j)
	{
		cpy[i] = str[j];
		cpy[j--] = str[i++];
	}
	ft_strdel(&str);
	return (cpy);
}

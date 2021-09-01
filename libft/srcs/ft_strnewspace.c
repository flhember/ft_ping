/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:23:44 by flhember          #+#    #+#             */
/*   Updated: 2019/05/02 17:15:43 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnewspace(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!(str = (char*)ft_memalloc(sizeof(char) * (size + 1))))
		return (0);
	while (i < size)
		str[i++] = ' ';
	return (str);
}

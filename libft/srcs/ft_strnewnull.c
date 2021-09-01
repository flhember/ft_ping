/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnewnull.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 12:42:33 by flhember          #+#    #+#             */
/*   Updated: 2019/04/03 12:43:07 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnewnull(char *str, size_t size)
{
	ft_strdel(&str);
	if (!(str = (char*)ft_memalloc(sizeof(char) * (size + 1))))
		return (0);
	return (str);
}

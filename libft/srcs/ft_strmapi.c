/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:55:35 by flhember          #+#    #+#             */
/*   Updated: 2019/01/24 16:00:44 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*cpy;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(cpy = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (i < ft_strlen(s))
	{
		cpy[i] = (*f)(i, s[i]);
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

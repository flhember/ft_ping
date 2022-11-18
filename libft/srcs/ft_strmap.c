/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:32:36 by flhember          #+#    #+#             */
/*   Updated: 2019/01/24 16:01:03 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*cpy;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(cpy = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (i < ft_strlen(s))
	{
		cpy[i] = (*f)(s[i]);
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

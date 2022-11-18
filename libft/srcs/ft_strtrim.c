/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 16:51:14 by flhember          #+#    #+#             */
/*   Updated: 2019/01/24 15:56:28 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	size;
	char	*str;
	size_t	sizefin;

	if (s)
	{
		i = 0;
		size = ft_strlen(s) - 1;
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
			i++;
		if (s[i] == '\0')
			return (ft_strdup(s + i));
		while (s[size] == ' ' || s[size] == '\n' || s[size] == '\t')
			size--;
		sizefin = size - i + 1;
		if (!(str = ft_strsub(s, i, sizefin)))
			return (NULL);
		return (str);
	}
	return (0);
}

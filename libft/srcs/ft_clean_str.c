/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:12:40 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:00:54 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_clean_str(char *str)
{
	int		i;
	char	*str_final;

	i = 0;
	str_final = NULL;
	while (str[i] == '0' && str[i + 1] == '0')
		i++;
	if (i > 0)
	{
		str_final = ft_strsub(str, i, ft_strlen(str) - i);
		ft_strdel(&str);
		return (str_final);
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 19:49:48 by flhember          #+#    #+#             */
/*   Updated: 2019/01/24 16:01:51 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int n)
{
	char	*jo;

	jo = ft_strjoin(s1, s2);
	if (n == 1)
		ft_strdel(&s1);
	if (n == 2)
		ft_strdel(&s2);
	if (n == 3)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	return (jo);
}

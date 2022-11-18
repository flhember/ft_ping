/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:00:17 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/03 14:32:38 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_count_c(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == c)
				count++;
			i++;
		}
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisalpha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:11:42 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/03 14:31:21 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_strisalpha(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
			i++;
		else
			return (-1);
	}
	return (1);
}

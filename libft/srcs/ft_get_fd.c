/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:47:08 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/18 18:15:41 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_get_fd(int fd)
{
	char	*line;
	int		res;
	int		nu;

	nu = 0;
	while ((res = get_next_line(fd, &line, &nu)) > 0)
	{
		if (line != NULL && nu == 1)
		{
			ft_strdel(&line);
			return (NULL);
		}
		return (line);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:46:07 by flhember          #+#    #+#             */
/*   Updated: 2020/01/17 17:03:13 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int			i;
	int			signe;
	long long	rep;

	rep = 0;
	signe = 0;
	i = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == ' ' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rep = (rep * 10) + str[i++] - 48;
		if (rep < 0)
			return (signe ? 0 : -1);
	}
	return (signe ? (int)-rep : (int)rep);
}

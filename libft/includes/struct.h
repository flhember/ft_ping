/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:37:56 by flhember          #+#    #+#             */
/*   Updated: 2020/02/14 11:45:21 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdlib.h>

typedef struct				s_conv
{
	char					*(*f)(va_list ap, char *str);
	struct s_conv			*next;
	char					type;
	char					pad[7];
}							t_conv;

typedef struct				s_option
{
	size_t					min;
	size_t					plus;
	size_t					minus;
	size_t					hash;
	size_t					space;
	size_t					zero;
	char					*size;
	char					*option;
	int						prec;
	char					flag;
	char					pad[3];
}							t_option;

typedef	struct				s_ftoa
{
	char					*mant;
	char					*expo;
	int						signe;
	char					pad[4];
}							t_ftoa;

typedef	union				u_ftoa64
{
	double					d;
	struct
	{
		unsigned long long	mant1 : 52;
		unsigned int		expo : 11;
		unsigned int		signe : 1;
	}						bin;
}							t_ftoa64;

typedef	union				u_ftoa80
{
	long double				d;
	struct
	{
		unsigned long long	mant1 : 64;
		unsigned int		expo : 15;
		unsigned int		signe : 1;
		char				pad[6];
	}						bin;
}							t_ftoa80;

#endif

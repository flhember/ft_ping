/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:45:35 by flhember          #+#    #+#             */
/*   Updated: 2020/02/14 11:21:59 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "struct.h"
# include "libft.h"

# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define BLU	"\x1B[34m"
# define MAG	"\x1B[35m"
# define CYN	"\x1B[36m"
# define WHT	"\x1B[37m"
# define RESET	"\x1B[0m"

int			ft_printf(char *str, ...);
void		ft_creatlst(t_conv	**list);
char		**ft_set_tab(char *str, char **tab_final);
char		**ft_convert_param(char **tab, t_conv **list, va_list ap);
char		*ft_convert_c(va_list ap, char *str);
char		*ft_convert_s(va_list ap, char *str);
char		*ft_convert_p(va_list ap, char *str);
char		*ft_convert_i_d(va_list ap, char *str);
char		*ft_convert_o(va_list ap, char *str);
char		*ft_convert_x(va_list ap, char *str);
char		*ft_convert_u(va_list ap, char *str);
char		*ft_convert_f(va_list ap, char *str);
char		*ft_convert_b(va_list ap, char *str);
char		*ft_convert_percent(va_list ap, char *str);
long long	ft_print_tab(char **tab, int i);
void		ft_free_list(t_conv **list);
void		ft_free_ftoa(t_ftoa **list);
void		ft_free_tab(char **tab);
t_option	*ft_get_option(char *str);
void		ft_set_list(t_option **list);
char		*ft_get_good_size_signed(va_list ap, t_option **list);
char		*ft_get_good_size_unsigned(va_list ap, t_option **list, int base);
char		*ft_get_size_unsigned_big(va_list ap, t_option **list, int base);
char		*ft_put_num(char *str, char *var, t_option **list, size_t size);
char		*ft_put_signe(char *str, char *var, t_option **list, size_t size);
char		*ft_put_zero(char *str, char *var, t_option **list);
char		*ft_put_zero_minus(char *str, char *var, t_option **list);
char		*ft_put_hash_x(char *str, char *var, t_option **list);
char		*ft_filling_zero_neg(char *str, t_option **list);
void		ft_free_option(t_option **list);
char		*ft_ftoa_dbl(double f, int prec, int hash);
char		*ft_add_str(char *s1, char *s2);
char		*ft_mult_str(char *str_fl, char *str_en);
char		*ft_pow_to_str(long b);
char		*ft_put_point(char *str, int vir);
char		*ft_ld_in_str(long double res, int i);
char		*ft_check_size(char *str);
int			ft_size_vir(long double f);
char		*ft_get_round(char *str, int i);
char		*ft_cut_prec(char *str, int prec, int vir, int hash);
char		*ft_ldtoa(long double res);
char		*ft_ftoa_ldbl(long double f, int prec, int hash);
char		*ft_nan_inf(t_ftoa **list);
char		*ft_zero_prec(char *str, int i);
char		*ft_check_hash(char *str, int hash);
char		*ft_good_var(va_list ap, t_option **list);
void		ft_free_float(t_option **list, char *str, char *var);
char		*ft_return_null_x(t_option **list, char *str, char *var_hexa);
void		ft_verif_size(char **s1, char **s2);
void		ft_put_flag_size(char *str, int i, t_option **list);
char		*ft_get_round_after(char *str, int i);
char		**ft_check_percent(char **tab);

#endif

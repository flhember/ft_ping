/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:13:18 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 17:20:51 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 8

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "ft_printf.h"

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
	size_t			content_size;
}					t_list;

char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strdup(const char *s);
size_t				ft_strlen(const char *str);
char				*ft_strcat(char *dest, const char *src);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_print_list(t_list *list);
char				*ft_strjoinfree(char *s1, char *s2, int n);
void				ft_swap(int *a, int *b);
int					ft_str_is_lowercase(char *str);
int					ft_str_is_uppercase(char *str);
int					ft_intlen(long long n);
char				*ft_lltoa(long long n);
char				*ft_strnewspace(size_t size);
char				*ft_ultoa_base(unsigned long n, int base);
char				*ft_ultoa_base_big(unsigned long n, int base);
long double			ft_pow(long double a, long double b);
char				*ft_str_rev(char *str);
char				*ft_strnewnull(char *str, size_t size);
char				*ft_clean_str(char *str);
void				ft_free_tab_int(int ***tab, int size);
int					get_next_line(const int fd, char **line, int *nl);
char				*ft_get_fd(int fd);
int					ft_rec_c(char *str, char c);
void				ft_free_tab_char(char **tab);
int					ft_count_c(char *str, char c);
int					ft_strisdigit(char *str);
int					ft_is_c(char *str, char c);
int					ft_strisalpha(char *str);
int					ft_strnalpha(char *str);
size_t				ft_strnlen(char *str, char c);
char				*ft_strncut(char *str, int n);

#endif

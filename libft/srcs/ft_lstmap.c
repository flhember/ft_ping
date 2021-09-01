/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:28:53 by flhember          #+#    #+#             */
/*   Updated: 2019/01/24 15:53:13 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin;
	t_list	*cpy;

	if (!lst || !f)
		return (NULL);
	begin = f(lst);
	cpy = begin;
	while (lst->next)
	{
		lst = lst->next;
		cpy->next = f(lst);
		cpy = cpy->next;
	}
	return (begin);
}

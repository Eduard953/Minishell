/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelat_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:39:30 by pstengl           #+#    #+#             */
/*   Updated: 2021/10/11 11:53:53 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelat(t_list **lst, int n, void (*f)(void *))
{
	t_list	*elem;

	if (n < 0)
		n = ft_lstsize(*lst) + n;
	elem = ft_lstat(*lst, n);
	if (f)
		f(elem->content);
	if (ft_lstat(*lst, n + 1))
	{
		if (n > 0 && ft_lstat(*lst, n - 1))
			(ft_lstat(*lst, n - 1)->next) = ft_lstat(*lst, n + 1);
		else
			*lst = (*lst)->next;
	}
	else
	{
		if (n == 0)
			*lst = NULL;
		else
			ft_lstat(*lst, n - 1)->next = NULL;
	}
	free(elem);
	return ;
}

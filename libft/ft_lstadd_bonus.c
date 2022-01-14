/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:09:25 by pstengl           #+#    #+#             */
/*   Updated: 2021/09/08 17:02:34 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **lst, void *content)
{
	t_list	*new_lst;

	new_lst = ft_lstnew(content);
	if (*lst == NULL)
		*lst = new_lst;
	else
		ft_lstlast(*lst)->next = new_lst;
}

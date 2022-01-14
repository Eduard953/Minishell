/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:22:10 by pstengl           #+#    #+#             */
/*   Updated: 2021/10/11 14:45:42 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstat(t_list *lst, int n)
{
	int	lstlen;
	int	index;

	if (n < 0)
	{
		lstlen = ft_lstsize(lst);
		n = lstlen + n;
	}
	if (n < 0)
		return (NULL);
	if (n > ft_lstsize(lst))
		return (NULL);
	index = 0;
	while (index < n)
	{
		if (lst->next == NULL)
			return (NULL);
		lst = lst->next;
		index++;
	}
	return (lst);
}

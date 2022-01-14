/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlst_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:22:11 by pstengl           #+#    #+#             */
/*   Updated: 2021/10/15 12:07:49 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printlst(t_list *lst)
{
	int	printed;

	if (!lst)
	{
		ft_print("[]");
		return (2);
	}
	printed = 0;
	printed += ft_print("[");
	while (1)
	{
		printed += ft_print("'");
		printed += ft_print((char *)lst->content);
		printed += ft_print("'");
		if (lst->next == NULL)
			break ;
		lst = lst->next;
		printed += ft_print(", ");
	}
	printed += ft_print("]");
	return (printed);
}

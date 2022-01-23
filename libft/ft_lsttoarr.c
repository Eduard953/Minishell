/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:58:35 by pstengl           #+#    #+#             */
/*   Updated: 2022/01/23 16:15:05 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lsttoarr(t_list *lst)
{
	char	**arr;
	int		i;

	if (lst == NULL)
		return (NULL);
	arr = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (1)
	{
		arr[i] = ft_strdup(lst->content);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
		i++;
	}
	return (arr);
}

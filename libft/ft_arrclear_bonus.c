/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:58:57 by pstengl           #+#    #+#             */
/*   Updated: 2022/02/24 17:50:09 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_arrclear(char **arr, void (*f)(void *content))
{
	int	index;

	if (!arr)
		return ;
	index = 0;
	while (arr[index])
	{
		f(arr[index]);
		arr[index] = NULL;
		index++;
	}
	free(arr);
	arr = NULL;
}

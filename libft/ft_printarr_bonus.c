/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printarr_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:52:41 by pstengl           #+#    #+#             */
/*   Updated: 2021/06/30 17:32:04 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printarr(char **arr)
{
	int	printed;

	printed = 0;
	if (arr == NULL)
		return (0);
	printed += ft_print("[");
	while (1)
	{
		printed += ft_print("'");
		printed += ft_print(*arr);
		printed += ft_print("'");
		if (!*(arr + 1))
			break ;
		printed += ft_print(", ");
		arr++;
	}
	printed += ft_print("]");
	return (printed);
}

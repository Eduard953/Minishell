/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printintarr_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:20:35 by pstengl           #+#    #+#             */
/*   Updated: 2021/06/30 17:33:47 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printintarr(int	*arr, size_t len)
{
	int		printed;
	size_t	index;

	index = 0;
	printed = 0;
	printed += ft_print("[");
	while (1)
	{
		printed += ft_printint(*arr);
		if (index + 1 >= len)
			break ;
		printed += ft_print(", ");
		arr++;
		index++;
	}
	printed += ft_print("]");
	return (printed);
}

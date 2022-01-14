/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isoneof_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 15:02:38 by pstengl           #+#    #+#             */
/*   Updated: 2021/06/17 15:06:04 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isoneof(const char c, const char *ref)
{
	if (!ref)
		return (0);
	if (c == '\0')
		return (0);
	while (*ref)
	{
		if (*ref == c)
			return (1);
		ref++;
	}
	return (0);
}

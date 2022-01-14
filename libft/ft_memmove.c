/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:48:10 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/19 17:05:06 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	temp;

	if (n > 0)
	{
		temp = *(unsigned char *)src;
		dest = ft_memmove(((unsigned char *)dest + 1),
				((unsigned char *)src + 1), n - 1);
		*(((unsigned char *)dest) - 1) = temp;
		return (((unsigned char *)dest) - 1);
	}
	return ((unsigned char *)dest);
}

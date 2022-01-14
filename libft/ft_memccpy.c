/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:33:50 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/18 11:30:25 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			counter;
	unsigned char	character;
	unsigned char	*to;
	unsigned char	*from;

	character = (unsigned char)c;
	to = (unsigned char *)dest;
	from = (unsigned char *)src;
	counter = 0;
	while (counter < n)
	{
		to[counter] = from[counter];
		if (from[counter] == character)
		{
			return ((void *)(to + counter + 1));
		}
		counter++;
	}
	return (NULL);
}

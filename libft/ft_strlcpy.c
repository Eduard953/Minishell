/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 20:50:11 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/16 11:42:32 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	try_to_create_len;

	try_to_create_len = ft_strlen(src);
	if (size == 0)
		return (try_to_create_len);
	while (*src != '\0' && (size - 1) > 0)
	{
		*dst = *src;
		dst++;
		src++;
		size--;
	}
	while (size > 0)
	{
		*dst = '\0';
		size--;
	}
	return (try_to_create_len);
}

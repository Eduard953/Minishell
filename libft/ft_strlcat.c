/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 21:10:55 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/21 11:19:25 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	try_to_create_len;
	size_t	dst_len;

	dst_len = 0;
	while (dst[dst_len] != '\0' && dst_len < size)
		dst_len++;
	dst = (dst + dst_len);
	try_to_create_len = dst_len + ft_strlen(src);
	if (size == 0 || *dst != '\0')
		return (try_to_create_len);
	size = size - dst_len;
	ft_strlcpy(dst, src, size);
	return (try_to_create_len);
}

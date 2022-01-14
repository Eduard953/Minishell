/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:08:46 by pstengl           #+#    #+#             */
/*   Updated: 2021/06/02 18:05:24 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static char	*ft_find_substr(const char *s1, const char *s2, size_t n)
{
	size_t	counter;

	counter = 0;
	while (*s1 != '\0' && counter <= n)
	{
		if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
			return ((char *)s1);
		s1++;
		counter++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s2_len == 0)
		return ((char *)s1);
	if (s2_len > s1_len || s2_len > n)
		return (NULL);
	n = n - s2_len;
	return (ft_find_substr(s1, s2, n));
}

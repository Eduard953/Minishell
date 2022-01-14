/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:45:59 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/27 21:56:14 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_set(const char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static size_t	ft_get_len(const char *s1, const char *set)
{
	size_t	len;
	size_t	search;

	len = 0;
	while (s1[len])
	{
		search = len;
		while (s1[search])
		{
			if (!ft_in_set(s1[search], set))
				break ;
			search++;
		}
		if (s1[search] == '\0')
			return (len);
		len++;
	}
	return (len);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	len;
	char	*result;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_in_set(*s1, set))
		s1++;
	len = ft_get_len(s1, set);
	result = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(result, s1, len + 1);
	if (!result)
		return (NULL);
	return (result);
}

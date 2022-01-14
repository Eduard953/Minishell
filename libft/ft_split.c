/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 12:39:16 by pstengl           #+#    #+#             */
/*   Updated: 2021/09/08 17:16:16 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_make_str(const char *s, char c)
{
	size_t	str_len;
	size_t	count;
	char	*my_str;

	str_len = 0;
	while (s[str_len] && s[str_len] != c)
		str_len++;
	my_str = ft_calloc(sizeof(char), str_len + 1);
	if (!my_str)
		return (NULL);
	count = 0;
	while (count < str_len)
	{
		my_str[count] = s[count];
		count++;
	}
	return (my_str);
}

static char	**ft_fill_arr(const char *s, char c, size_t index)
{
	size_t	count;
	char	*my_str;
	char	**split_prod;

	if (*s == '\0')
	{
		split_prod = ft_calloc(sizeof(char **), index + 1);
		if (!split_prod)
			return (NULL);
		return (split_prod);
	}
	my_str = ft_make_str(s, c);
	if (!my_str)
		return (NULL);
	count = ft_strlen(my_str);
	while (*(s + count) && *(s + count) == c)
		count++;
	split_prod = ft_fill_arr((s + count), c, index + 1);
	if (!split_prod)
	{
		free(my_str);
		return (NULL);
	}
	split_prod[index] = my_str;
	return (split_prod);
}

char	**ft_split(const char *s, char c)
{
	if (s == NULL)
		return (NULL);
	while (*s == c && *s)
		s++;
	return (ft_fill_arr(s, c, 0));
}

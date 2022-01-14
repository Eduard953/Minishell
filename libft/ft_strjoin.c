/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:46:36 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/19 12:40:13 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	final_size;
	size_t	index;
	char	*space;

	final_size = ft_strlen(s1) + ft_strlen(s2);
	space = malloc(final_size + 1);
	if (!space)
		return (NULL);
	index = 0;
	while (*s1)
	{
		space[index] = *s1;
		index++;
		s1++;
	}
	while (*s2)
	{
		space[index] = *s2;
		index++;
		s2++;
	}
	space[index] = '\0';
	return (space);
}

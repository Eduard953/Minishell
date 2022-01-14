/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:19:09 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/16 11:49:41 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	index;
	char	*space;

	space = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!space)
		return (NULL);
	index = 0;
	while (s[index])
	{
		space[index] = f(index, s[index]);
		index++;
	}
	space[index] = '\0';
	return (space);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 21:33:15 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/16 11:52:11 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	counter;

	counter = ft_strlen(s);
	while (1)
	{
		if (s[counter] == c)
			return ((char *)(&s[counter]));
		if (counter == 0)
			break ;
		counter--;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strext_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 15:43:51 by pstengl           #+#    #+#             */
/*   Updated: 2021/06/17 15:45:17 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strext(char **base, char *ext, size_t size)
{
	char	*temp;
	size_t	count;
	size_t	base_len;

	base_len = ft_strlen(*base);
	if (ft_strlen(ext) < size)
		size = ft_strlen(ext);
	temp = ft_calloc(sizeof(char *), base_len + size + 1);
	if (temp == NULL)
		return (NULL);
	count = 0;
	while (*base && (*base)[count])
	{
		temp[count] = (*base)[count];
		count++;
	}
	free(*base);
	count = 0;
	while (ext[count] && count < size)
	{
		temp[count + base_len] = ext[count];
		count++;
	}
	*base = temp;
	return (temp);
}

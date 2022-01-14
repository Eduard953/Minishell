/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:46:46 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/27 20:18:11 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	final_size;
	void	*space;

	final_size = nmemb * size;
	if (final_size != 0)
		if (final_size / nmemb != size)
			return (NULL);
	space = malloc(final_size);
	if (space == NULL)
		return (NULL);
	ft_bzero(space, final_size);
	return (space);
}

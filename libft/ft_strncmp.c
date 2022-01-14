/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:25:08 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/21 23:31:04 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (ft_strlen(s1) < n)
		n = ft_strlen(s1) + 1;
	if (ft_strlen(s2) < n)
		n = ft_strlen(s2) + 1;
	return (ft_memcmp(s1, s2, n));
}

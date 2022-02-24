/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestrlen_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:47:03 by pstengl           #+#    #+#             */
/*   Updated: 2022/02/24 12:51:00 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "./libft.h"

size_t	ft_freestrlen(const char *str, void (*f)(void *))
{
	size_t	len;

	len = ft_strlen(str);
	f((void *)str);
	return (len);
}

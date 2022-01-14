/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:00:13 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/26 16:00:57 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_rec(int n, size_t len, int neg)
{
	size_t	str_len;
	char	*str;

	if (n / 10 == 0)
	{
		if (neg)
		{
			str = ft_calloc(len + 2, 1);
			str[0] = '-';
		}
		else
			str = ft_calloc(len + 1, 1);
	}
	else
		str = ft_rec(n / 10, len + 1, neg);
	str_len = ft_strlen(str);
	str[str_len] = (n % 10) + 48;
	return (str);
}

char	*ft_itoa(int n)
{
	int	neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = 0;
	if (n < 0)
	{
		n = n * -1;
		neg = 1;
	}
	return (ft_rec(n, 1, neg));
}

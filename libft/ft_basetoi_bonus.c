/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basetoi_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:32:09 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/21 22:44:53 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_base(char c, const char *base)
{
	while (*base)
	{
		if (*base == c)
			return (1);
		base++;
	}
	return (0);
}

static int	index_of(const char *str, char c)
{
	int	index;

	index = 0;
	while (*str)
	{
		if (*str == c)
			return (index);
		index++;
		str++;
	}
	return (-1);
}

int	ft_basetoi(const char *nb, const char *base)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*nb))
		nb++;
	if (*nb == '-')
	{
		sign = sign * -1;
		nb++;
	}
	while (*nb)
	{
		if (!(in_base(*nb, base)))
			break ;
		result = (result * ft_strlen(base)) + index_of(base, *nb);
		nb++;
	}
	return (sign * result);
}

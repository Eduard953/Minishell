/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitobase_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:53:16 by pstengl           #+#    #+#             */
/*   Updated: 2021/06/23 18:35:50 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*build_str_recursive(unsigned int num, unsigned int base_count,
		char *base, unsigned int index)
{
	char	*str;

	if (num / base_count == 0)
	{
		str = ft_calloc(sizeof(char), index + 2);
		str[0] = base[(num % base_count)];
		return (str);
	}
	str = build_str_recursive(num / base_count, base_count, base, index + 1);
	str[ft_strlen(str)] = base[(num % base_count)];
	return (str);
}

static unsigned int	check_base(const char *base)
{
	unsigned int	base_count;
	unsigned int	index;

	base_count = 0;
	while (base[base_count] != '\0')
	{
		index = 0;
		while (index < base_count)
		{
			if (base[base_count] == base[index])
				return (0);
			index++;
		}
		if (base[base_count] == '+' || base[base_count] == '-')
			return (0);
		base_count++;
	}
	return (base_count);
}

char	*ft_uitobase(unsigned int num, char *base)
{
	unsigned int	base_count;

	base_count = check_base(base);
	if (base_count == 0)
		return (NULL);
	return (build_str_recursive(num, base_count, base, 0));
}

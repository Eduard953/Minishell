/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itobase_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:58:30 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/21 20:00:24 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

static char	*convert(int nb, const char *base, size_t base_count, size_t index)
{
	size_t	str_len;
	char	*str;

	if (nb / base_count == 0)
		str = ft_calloc(sizeof(char), index + 1);
	else
		str = convert(nb / base_count, base, base_count, index + 1);
	str_len = ft_strlen(str);
	str[str_len] = base[nb % base_count];
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

char	*ft_itobase(int nb, const char *base)
{
	size_t			str_len;
	char			*str;
	char			*result;
	unsigned int	base_count;

	base_count = check_base(base);
	if (base_count < 2)
		return (NULL);
	if (nb == -2147483648)
		return (NULL);
	if (nb < 0)
	{
		nb = nb * -1;
		result = convert(nb, base, base_count, 1);
		str_len = ft_strlen(result);
		str = ft_calloc(str_len + 2, 1);
		str[0] = '-';
		ft_strlcat(str, result, str_len + 2);
		free(result);
		return (str);
	}
	return (convert(nb, base, base_count, 1));
}

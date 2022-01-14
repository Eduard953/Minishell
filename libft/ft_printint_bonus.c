/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:19:39 by pstengl           #+#    #+#             */
/*   Updated: 2021/06/30 17:36:21 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printint(int n)
{
	int		printed;
	char	*str;

	printed = 0;
	str = ft_itoa(n);
	printed += ft_print(str);
	free(str);
	return (printed);
}

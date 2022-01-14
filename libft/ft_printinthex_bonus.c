/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printinthex_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:29:33 by pstengl           #+#    #+#             */
/*   Updated: 2021/06/30 17:37:00 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printinthex(int n)
{
	int		printed;
	char	*result;

	printed = 0;
	result = ft_itohex(n);
	printed += ft_print(result);
	free(result);
	return (printed);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuint_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 13:10:55 by pstengl           #+#    #+#             */
/*   Updated: 2021/06/30 18:00:20 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printuint(unsigned int n)
{
	int	printed;

	printed = 0;
	if (n / 10 != 0)
		printed += ft_printuint(n / 10);
	printed += ft_printc((n % 10) + 48);
	return (printed);
}

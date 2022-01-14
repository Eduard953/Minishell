/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_println_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:18:36 by pstengl           #+#    #+#             */
/*   Updated: 2021/06/30 17:38:13 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_println(char *str)
{
	int	printed;

	printed = 0;
	if (str == NULL)
		return (0);
	printed += ft_print(str);
	printed += ft_printc('\n');
	return (printed);
}

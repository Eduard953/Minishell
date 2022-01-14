/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 13:10:55 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/26 15:37:29 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_rec(int n, int neg, int fd)
{
	if (n / 10 == 0)
	{
		if (neg)
			ft_putchar_fd('-', fd);
	}
	else
		ft_rec(n / 10, neg, fd);
	ft_putchar_fd((n % 10) + 48, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	neg;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	neg = 0;
	if (n < 0)
	{
		n = n * -1;
		neg = 1;
	}
	ft_rec(n, neg, fd);
}

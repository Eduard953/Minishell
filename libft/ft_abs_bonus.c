/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 17:10:11 by pstengl           #+#    #+#             */
/*   Updated: 2021/06/23 14:33:33 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs(const int num)
{
	if (num == -2147483648)
		return (2147483647);
	if (num < 0)
		return (num * -1);
	return (num);
}

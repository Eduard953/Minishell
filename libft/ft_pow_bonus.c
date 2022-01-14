/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:49:34 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/20 15:49:48 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_pow(int base, int exp)
{
	int	result;

	if (exp == 0)
		return (1);
	if (exp < 0)
		return (0);
	if (base == 0)
		return (0);
	result = base;
	if (exp - 1 > 0)
		result = base * ft_pow(base, exp - 1);
	return (result);
}

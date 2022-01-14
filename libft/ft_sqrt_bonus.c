/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:55:25 by pstengl           #+#    #+#             */
/*   Updated: 2021/05/20 15:55:28 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	index;

	if (nb <= 0)
		return (0);
	index = 1;
	while (index * index < nb)
	{
		if (index == 46340)
			break ;
		index++;
	}
	if (index * index == nb)
		return (index);
	return (0);
}

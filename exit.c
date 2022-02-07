/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:21:22 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/07 14:38:08 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnumber(char *num)
{
	int	i;

	i = -1;
	while (num[++i])
		if (!(ft_isdigit(num[i])))
			return (0);
	return (1);
}

int	builtin_exit(char **args)
{
	if (ft_arrlen(args) > 1)
		if (ft_isnumber(args[1]))
			exit(ft_atoi(args[1]));
	exit (0);
}

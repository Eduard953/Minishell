/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:21:22 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/24 11:44:50 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	ft_isnumber(char *num)
{
	int	i;

	i = -1;
	if (num[0] == '-' || num[0] == '+')
		i = 0;
	while (num[++i])
		if (!(ft_isdigit(num[i])))
			return (0);
	return (1);
}

int	check_arg(char **args)
{
	int	i;

	i = 1;
	if (ft_arrlen(args) > 2)
		return (error(1)); // need the right errorcodes
	while (args[i])
	{
		if (!ft_isnumber(args[i]))
			return (error(127)); // need the right errorcodes
		i++;
	}
	return (0);
}

int	builtin_exit(char **args, int returncode)
{
	if (check_arg(args))
		return (check_arg(args));
	if (ft_arrlen(args) == 2)
		returncode = ft_atoi(args[1]) % 256;
	//clean(); // Free all memory?
	exit(returncode);
}

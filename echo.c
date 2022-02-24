/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:15:21 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/24 15:32:01 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_minusn(char *str)
{
	if (!str)
		return (0);
	if (*str != '-')
		return (0);
	str++;
	while(*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	builtin_echo(char **args)
{
	int	argslen;
	int	newline;
	int	index;

	argslen = ft_arrlen(args);
	newline = 1;
	index = 1;
	if (argslen > 1)
	{
		while (find_minusn(args[index]) && index < argslen)
		{
			newline = 0;
			index++;
		}
		while (index < argslen)
		{
			printf("%s", args[index]);
			index++;
			if (index < argslen)
				printf(" ");
		}
	}
	if (newline)
		printf("\n");
	return (0);
}

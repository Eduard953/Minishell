/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:15:21 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/11 18:13:55 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strcmp(args[index], "-n") == 0)
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

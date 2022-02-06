/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:15:21 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/06 15:18:44 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **args)
{
	int	argslen;
	int	newline;
	int	index;

	argslen = 0;
	while (args[argslen] != NULL)
		argslen++;
	newline = 1;
	index = 1;
	if (ft_strcmp(args[index], "-n") == 0 && (argslen > 1))
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
	if (newline)
		printf("\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:16:12 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/31 13:52:17 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_cd(char **args, char **envp) 
{
	int	argslen;
	int	returnval;

	argslen = 0;
	returnval = -1;
	while(args[argslen] != NULL)
		argslen++;
	if (argslen == 1)
	{
		returnval = chdir(ft_in_envp(envp, "HOME"));
	}
	else if (argslen == 2)
		returnval = chdir(args[1]);
	else
		return (error(7));
	if (returnval != 0)
		return (error(5));
	return(0);
}
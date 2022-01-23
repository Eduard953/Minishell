/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:16:12 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/23 16:09:44 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_cd(char **args, char **envp) 
{
	int	argslen;
	int	returnval;

	printf("Builtin cd\n");
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
		printf("cd: Too many arguments\n");
	if (returnval != 0)
		printf("cd: Error changing directory\n");
}
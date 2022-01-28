/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:16:12 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/28 13:27:46 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **builtin_cd(char **args, char **envp)
{
	int	argslen;
	int	returnval;
	char	**args_for_export;

	printf("Builtin cd\n");
	argslen = 0;
	returnval = -1;
	args_for_export = ft_calloc(3, sizeof(char *));
	args_for_export[0] = ft_strdup("export");
	args_for_export[1] = ft_strdup("OLDPWD=");
	args_for_export[1] = ft_strext(&args_for_export[1], cwd(), ft_strlen(cwd()));
	envp = builtin_export(args_for_export, envp);
	while(args[argslen] != NULL)
		argslen++;
	if (argslen == 1)
		returnval = chdir(ft_in_envp(envp, "HOME"));
	else if (argslen == 2)
		returnval = chdir(args[1]);
	else
	{
		printf("cd: Too many arguments\n");
		return envp;
	}
	if (returnval != 0)
	{
		printf("cd: Error changing directory\n");
		return envp;
	}
	free(args_for_export[1]);
	args_for_export[1] = ft_strdup("PWD=");
	args_for_export[1] = ft_strext(&args_for_export[1], cwd(), ft_strlen(cwd()));
	envp = builtin_export(args_for_export, envp);
	free(args_for_export[0]);
	free(args_for_export[1]);
	free(args_for_export);
	return envp;
}

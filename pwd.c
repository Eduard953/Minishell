/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:00:54 by pstengl           #+#    #+#             */
/*   Updated: 2022/02/25 16:48:33 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(char ***envp)
{
	char	*path_arg;
	char	*path;
	char	*args[3];

	path_arg = NULL;
	path_arg = ft_strext(&path_arg, "PWD=", 4);
	path = cwd();
	path_arg = ft_strext(&path_arg, path, ft_strlen(path));
	free(path);
	args[0] = "export";
	args[1] = path_arg;
	args[2] = NULL;
	builtin_export(args, envp);
	free(path_arg);
}

int	builtint_pwd(void)
{
	char	*path;

	path = ft_calloc(1024, 1);
	getcwd(path, 1024);
	ft_println(path);
	free(path);
	return (0);
}

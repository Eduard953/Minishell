/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:45:42 by pstengl           #+#    #+#             */
/*   Updated: 2022/02/25 13:16:30 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_arg_with_path(char ***arg, char **envp)
{
	char	*path;

	if (!ft_isalpha((*arg)[0][0]))
		return (0);
	path = find_in_path((*arg)[0], envp);
	if (path == NULL)
	{
		ft_putstr_fd("Command not Found\n", 2);
		return (1);
	}
	free((*arg)[0]);
	(*arg)[0] = path;
	return (0);
}

int	run_external(char **arg, char **envp, int wait_finish)
{
	int		pid;
	int		returncode;

	if (replace_arg_with_path(&arg, envp))
		return (127);
	pid = fork();
	if (!pid)
	{
		execve(arg[0], arg, envp);
		perror("execve");
		exit(1);
	}
	if (!wait_finish)
		return (0);
	waitpid(pid, &returncode, 0);
	if (WIFEXITED(returncode))
		return (WEXITSTATUS(returncode));
	return (0);
}

int	launch_exe(char **arg, char ***envp, int returncode, int wait_finish)
{
	if (ft_strcmp(arg[0], "echo") == 0)
		return (builtin_echo(arg));
	if (ft_strcmp(arg[0], "cd") == 0)
		return (builtin_cd(arg, envp));
	if (ft_strcmp(arg[0], "exit") == 0)
		return (builtin_exit(arg, returncode));
	if (ft_strcmp(arg[0], "env") == 0)
		return (builtin_env((*envp)));
	if (ft_strcmp(arg[0], "export") == 0)
		return (builtin_export(arg, envp));
	if (ft_strcmp(arg[0], "unset") == 0)
	{
		(*envp) = builtin_unset(arg, (*envp));
		return (0);
	}
	if (ft_strcmp(arg[0], "pwd") == 0)
		return (builtint_pwd());
	return (run_external(arg, *envp, wait_finish));
}

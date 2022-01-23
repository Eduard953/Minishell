/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:18:36 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/23 16:38:15 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**execute_command(t_list *commands, char **envp)
{
	t_instruction *instr;
	pid_t	ret;
	char	**arg;

	while(commands)
	{
		instr = commands->content;
		arg = replace_arg(instr->command);
		ft_print("What is here? ");
		ft_printarr(arg);
		ft_println("");
		if (ft_strcmp(arg[0], "echo") == 0)
		{
			builtin_echo(arg);
			commands = commands->next;
			continue;
		}
		if (ft_strcmp(arg[0], "cd") == 0)
		{
			builtin_cd(arg, envp);
			commands = commands->next;
			continue;
		}
		if (ft_strcmp(arg[0], "exit") == 0)
		{
			builtin_exit();
			commands = commands->next;
			continue;
		}
		if (ft_strcmp(arg[0], "env") == 0)
		{
			builtin_env(envp);
			commands = commands->next;
			continue;
		}
		if (ft_strcmp(arg[0], "export") == 0)
		{
			envp = builtin_export(arg, envp);
			commands = commands->next;
			continue;
		}
		if (ft_strcmp(arg[0], "unset") == 0)
		{
			envp = builtin_unset(arg, envp);
			commands = commands->next;
			continue;
		}
		if (ft_isalpha(arg[0][0])) {
			arg[0] = find_in_path(arg[0], envp);
			if (arg[0] == NULL) {
				printf("Executable not found in PATH\n");
				return (envp);
			}
		}
		ret = fork();
		if (!ret)
		{
			execve(arg[0], arg, envp);
			free(arg);
			perror("execve");
			exit(1);
		}
		waitpid(ret, NULL, 0);
		commands = commands->next;
	}
	return(envp);
}

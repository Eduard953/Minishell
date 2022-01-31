/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:18:36 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/31 14:18:55 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_exe(char **arg, char ***in_envp)
{
	char	**envp;
	int		pid;

	envp = *in_envp;
	if (ft_strcmp(arg[0], "echo") == 0)
		return (builtin_echo(arg));
	if (ft_strcmp(arg[0], "cd") == 0)
		return (builtin_cd(arg, &envp));
	if (ft_strcmp(arg[0], "exit") == 0)
	{
		builtin_exit();
		return (0);
	}
	if (ft_strcmp(arg[0], "env") == 0)
		return (builtin_env(envp));
	if (ft_strcmp(arg[0], "export") == 0)
		return (builtin_export(arg, &envp));
	if (ft_strcmp(arg[0], "unset") == 0)
	{
		envp = builtin_unset(arg, envp);
		return (0);
	}
	if (ft_strcmp(arg[0], "pwd") == 0)
		return (builtint_pwd());

	if (ft_isalpha(arg[0][0]))
	{
		arg[0] = find_in_path(arg[0], envp);
		if (arg[0] == NULL)
			return (error(127));
	}
	pid = fork();
	if (!pid)
	{
		execve(arg[0], arg, envp);
		perror("execve");
		exit(1);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int execute_command(t_list *commands, char ***in_envp)
{
	t_instruction *instr;
	char	**arg;
	char	**envp;
	int		save_stdin;
	int		save_stdout;
	int		fdin;
	int		fdout;
	int		fdpipe[2];
	int		returncode;

	save_stdin = dup(0);
	save_stdout = dup(1);
	envp = *in_envp;

	while(commands)
	{
		instr = commands->content;
		arg = replace_arg(instr->command);
		if (!arg)
		{
			commands = commands->next;
			continue;
		}
		// Input redirections
		if (ft_strcmp(instr->in, "#stdin") == 0)
			fdin = dup(save_stdin);
		else if (ft_strncmp(instr->in, "#text", 5) == 0)
		{
			fdin = open("./.mstmp", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			write(fdin, instr->in+5, ft_strlen(instr->in)-5);
			close(fdin);
			fdin = open("./.mstmp", O_RDONLY);
		}
		else if (ft_strcmp(instr->in, "#pipe") != 0)
			fdin = open(instr->in, O_RDONLY);
		if (fdin < 0)
		{
			perror("Pipes");
			ft_arrclear(arg, free);
			return(1);
		}
		dup2(fdin, 0);
		close(fdin);
		// Output redirections
		if (ft_strcmp(instr->out, "#stdout") == 0)
			fdout = dup(save_stdout);
		else if (ft_strcmp(instr->out, "#pipe") == 0)
		{
			pipe(fdpipe);
			fdin = fdpipe[0];
			fdout = fdpipe[1];
		}
		else if (ft_strncmp(instr->out, "#append", 7) == 0)
			fdout = open(instr->out+7, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		else
			fdout = open(instr->out, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		if (fdout < 0)
		{
			perror("Pipes");
			ft_arrclear(arg, free);
			return(1);
		}
		dup2(fdout, 1);
		close(fdout);
		returncode = launch_exe(arg, &envp);
		ft_arrclear(arg, free);
		commands = commands->next;
	}
	dup2(save_stdin, 0);
	dup2(save_stdout, 1);
	close(save_stdin);
	close(save_stdout);
	unlink("./.mstmp");
	*in_envp = envp;
	return(returncode);
}

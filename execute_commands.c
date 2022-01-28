/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:18:36 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/28 14:43:05 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>

int	launch_exe(char **arg, char ***in_envp)
{
	char	**envp;
	int		pid;

	envp = *in_envp;
	if (ft_strcmp(arg[0], "echo") == 0)
		builtin_echo(arg);
	if (ft_strcmp(arg[0], "cd") == 0)
		envp = builtin_cd(arg, envp);
	if (ft_strcmp(arg[0], "exit") == 0)
		builtin_exit();
	if (ft_strcmp(arg[0], "env") == 0)
		builtin_env(envp);
	if (ft_strcmp(arg[0], "export") == 0)
		envp = builtin_export(arg, envp);
	if (ft_strcmp(arg[0], "unset") == 0)
		envp = builtin_unset(arg, envp);
	if (ft_strcmp(arg[0], "pwd") == 0)
		builtint_pwd();

	if (ft_isalpha(arg[0][0])) {
		arg[0] = find_in_path(arg[0], envp);
		if (arg[0] == NULL) {
			printf("Executable not found in PATH\n");
			return (127);
		}
	}
	pid = fork();
	if (!pid)
	{
		execve(arg[0], arg, envp);
		free(arg);
		perror("execve");
		exit(1);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

char	**execute_command(t_list *commands, char **envp)
{
	t_instruction *instr;
	char	**arg;
	int		save_stdin;
	int		save_stdout;
	int		fdin;
	int		fdout;
	int		fdpipe[2];

	save_stdin = dup(0);
	save_stdout = dup(1);

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
		{
			fdin = dup(save_stdin);
			ft_println("STDIN");
		}
		else if (ft_strncmp(instr->in, "#text", 5) == 0)
		{
			fdin = open("./.mstmp", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			write(fdin, instr->in+5, ft_strlen(instr->in)-5);
			close(fdin);
			fdin = open("./.mstmp", O_RDONLY);
		}
		else if (ft_strcmp(instr->in, "#pipe") != 0)
		{
			fdin = open(instr->in, O_RDONLY);
			ft_println("FILEIN");
		}
		if (fdin < 0)
		{
			ft_println("Error Input file could not be opened!");
			return (envp);
		}
		dup2(fdin, 0);
		close(fdin);
		// Output redirections
		if (ft_strcmp(instr->out, "#stdout") == 0)
		{
			fdout = dup(save_stdout);
			ft_println("STDOUT");
		}
		else if (ft_strcmp(instr->out, "#pipe") == 0)
		{
			pipe(fdpipe);
			fdin = fdpipe[0];
			fdout = fdpipe[1];
			ft_println("PIPEOUT");
		}
		else if (ft_strncmp(instr->out, "#append", 7) == 0)
		{
			fdout = open(instr->out+7, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
			ft_println("APPEND");
		}
		else
		{
			fdout = open(instr->out, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			ft_println("WRITE");
		}
		if (fdout < 0)
		{
			ft_println("Error Output file could not be opened!");
			return (envp);
		}
		dup2(fdout, 1);
		close(fdout);
		ft_print("What is here? ");
		ft_printarr(arg);
		ft_println("");
		launch_exe(arg, &envp);
		commands = commands->next;
	}
	dup2(save_stdin, 0);
	dup2(save_stdout, 1);
	close(save_stdin);
	close(save_stdout);
	unlink("./.mstmp");
	return(envp);
}

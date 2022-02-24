/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:18:36 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/24 17:46:11 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_inred(char *filename, int *fd, int *fd_save)
{
	if (ft_strcmp(filename, "#stdin") == 0)
		fd[0] = dup(fd_save[0]);
	else if (ft_strncmp(filename, "#text", 5) == 0)
	{
		fd[0] = open("./.mstmp", O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);
		write(fd[0], filename + 5, ft_strlen(filename) - 5);
		close(fd[0]);
		fd[0] = open("./.mstmp", O_RDONLY);
	}
	else if (ft_strcmp(filename, "#pipe") != 0)
		fd[0] = open(filename, O_RDONLY);
	if (fd[0] < 0)
	{
		perror("Pipes");
		return (1);
	}
	dup2(fd[0], 0);
	close(fd[0]);
	return (0);
}

int	setup_outred(char *filename, int *fd, int *fd_save, int *fd_pipe)
{
	if (ft_strcmp(filename, "#stdout") == 0)
		fd[1] = dup(fd_save[1]);
	else if (ft_strcmp(filename, "#pipe") == 0)
	{
		pipe(fd_pipe);
		fd[0] = fd_pipe[0];
		fd[1] = fd_pipe[1];
	}
	else if (ft_strncmp(filename, "#append", 7) == 0)
		fd[1] = open(filename + 7, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR);
	else
		fd[1] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd[1] < 0)
	{
		perror("Pipes");
		return (1);
	}
	dup2(fd[1], 1);
	close(fd[1]);
	return (0);
}

char	**setup_command(t_instruction *instr, int *fd, int *fd_save)
{
	char			**arg;
	int				fd_pipe[2];

	arg = replace_arg(instr->command);
	if (!arg)
		return (NULL);
	if (!setup_inred(instr->in, fd, fd_save))
		return (NULL);
	if (!setup_outred(instr->out, fd, fd_save, fd_pipe))
		return (NULL);
	return (arg);
}

int	execute_command(t_list *commands, char ***envp, int returncode)
{
	char	**arg;
	int		fd[2];
	int		fd_save[2];

	fd_save[0] = dup(0);
	fd_save[1] = dup(1);
	while (commands)
	{
		arg = setup_command(commands->content, fd, fd_save);
		if (arg)
			returncode = launch_exe(arg, envp, returncode,
					commands->next == NULL);
		ft_arrclear(arg, free);
		commands = commands->next;
	}
	dup2(fd_save[0], 0);
	dup2(fd_save[1], 1);
	close(fd_save[0]);
	close(fd_save[1]);
	unlink("./.mstmp");
	return (returncode);
}

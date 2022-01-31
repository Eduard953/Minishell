/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:09:24 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/31 13:58:57 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
#include "./libft/libft.h"
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>

typedef struct s_data
{
	char	*line;
} t_data;

typedef struct s_instruction
{
	char	*command;
	char	*in;
	char	*out;
} t_instruction;


char	**execute_command(t_list *commands, char **envp);
int builtin_cd(char **args, char **envp);
int builtin_echo(char **args);
void	advance(char *line, int *index, int *start);
void	sig_handler(int signum);
int builtin_env(char **envp);
void builtin_exit(void);
t_instruction *instr_create(char *line, int length, char *in, char *out);
char	*build_prompt();
char	*ft_in_envp(char **envp, char *variable);
char	*replace_var(char *line, char **envp);
char **builtin_export(char **arg, char **envp);
char	*find_in_path(char *exec_name, char **envp);
char **replace_arg(char *line);
char **builtin_unset(char **arg, char **envp);
int	builtint_pwd(void);
int error(int errorcode);

#endif

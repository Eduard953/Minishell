/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:09:24 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/25 16:26:40 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_data
{
	t_list	*tokens;
	char	*line;
	char	*prompt;
	char	*rep_line;
	int		returncode;
}	t_data;

typedef struct s_instruction
{
	char	*command;
	char	*in;
	char	*out;
	char	*text;
}	t_instruction;

typedef struct s_int
{
	int		start;
	int		idx;
	int		len;
	int		is_q;
	char	quote;
}	t_int;

int				execute_command(t_list *commands, char ***envp, int returncode);
int				builtin_cd(char **args, char ***envp);
int				builtin_echo(char **args);
void			advance(char *line, int *index, int *start);
void			sig_handler(int signum);
int				builtin_env(char **envp);
int				builtin_exit(char **args, int returncode);
t_instruction	*instr_create(char *line, int length, char *in, char *out);
char			*build_prompt(void);
char			*ft_in_envp(char **envp, char *variable);
char			*replace_var(char *line, char **envp, int returncode);
int				builtin_export(char **arg, char ***envp);
char			*find_in_path(char *exec_name, char **envp);
char			**replace_arg(char *line);
char			**builtin_unset(char **arg, char **envp);
int				builtint_pwd(void);
int				error(int errorcode);
char			*cwd(void);
t_list			*find_token(char *line);
char			*find_fname(char *line);
int				ft_checkname(char *name);
void			del(void *content);
void			update_pwd(char ***envp);
void			init_ints(t_int *n);
char			*ft_in_envp(char **envp, char *variable);
char			**replace_arg(char *line);
char			*find_in_path(char *exec_name, char **envp);
int				red_left(char **line, int length, t_list **instructions);
int				red_right(char **in, char **line, int length,
					t_list **instructions);
void			handle_pipe(t_list **instructions, char **in,
					char **line, int *length);
void			handle_inred(t_list **instructions, char **in,
					char **line, int *length);
void			handle_outred(t_list **instructions, char **in,
					char **line, int *length);
int				handle_quotes(char **line, int *length);
int				handle_forbidden(char **line, int *length);
int				launch_exe(char **arg, char ***envp, int returncode,
					int wait_finish);
t_instruction	*newxt_instr(char *line, int length, t_list **instructions,
					char *in);
void			skip_spaces(char **line);

#endif

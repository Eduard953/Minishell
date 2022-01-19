/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:06:02 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/19 15:25:49 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./libft/libft.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>

char	*ft_in_envp(char **envp, char *variable)
{
	char **parts;
	char *value;
	int		i;

	value = NULL;
	while(*envp)
	{
		parts = ft_split(*envp, '=');
		if (parts)
		{
			if (ft_strcmp(parts[0], variable) == 0)
				value = ft_strdup(parts[1]);
			i = 0;
			while(parts[i])
			{
				free(parts[i]);
				i++;
			}
			free(parts);
		}
		if (value)
			break;
		envp++;
	}
	return (value);
}

void builtin_echo(char **args) {
	int	argslen;
	int	newline;
	int	index;

	printf("Builtin echo\n");
	argslen = 0;
	while(args[argslen] != NULL)
		argslen++;
	newline = 1;
	index = 1;
	if (argslen > 1) {
		if (ft_strcmp(args[index], "-n") == 0)
		{
			newline = 0;
			index++;
		}
	}
	while (index < argslen) {
		printf("%s", args[index]);
		index++;
		if (index < argslen) {
			printf(" ");
		}
	}
	if (newline)
		printf("\n");
}

void builtin_exit(void) {
	exit(0);
}

void builtin_env(char **envp) {
	while(*envp) {
		printf("%s\n", *envp);
		envp++;
	}
}

void builtin_cd(char **args, char **envp) {
	int	argslen;
	int	returnval;

	printf("Builtin cd\n");
	argslen = 0;
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

t_instruction *instr_create(char *line, int length, char *in, char *out)
{
	char			*command;
	t_instruction	*instr;

	command = ft_calloc(1, length+2);
	ft_strlcpy(command, line, length+1);
	instr = ft_calloc(1, sizeof(t_instruction));
	instr->command = ft_strtrim(command, " ");
	instr->in = in;
	instr->out = out;
	free(command);
	printf("Command: %s from %s to %s\n", instr->command, instr->in, instr->out);
	return (instr);
}

char	*find_filename(char *line)
{
	char	*filename;
	int		length;

	while (*line == ' ')
		line++;
	length = 0;
	while (line[length] != '\0' && line[length] != ' ')
		length++;
	filename = ft_calloc(1, length+1);
	ft_strlcpy(filename, line, length+1);
	printf("Filename: %s\n", filename);
	return (filename);
}

void	advance(char *line, int *index, int *start)
{
	//printf("We are at %d (start %d)\n", *index, *start);
	*start = (*index) + 1;
	while (line[*start] == ' ')
		(*start)++;
	*index = (*start) - 1;
	//printf("Advanced, now we are at %d (start %d)\n", *index, *start);
}

t_list	*find_token(char *line)
{
	int	start;
	int	index;
	char	*in;
	char	*out;
	t_instruction	*instr;
	t_list			*instructions;
	char	quote;

	start = 0;
	index = 0;
	instructions = NULL;
	in = "#stdin";
	out = "#stdout";
	while (line[index] != '\0')
	{
		if (line[index] == '<')
		{
			if (line[index+1] == '<')
				printf("DOUBLE REDIRECT"); //TODO
			instr = instr_create(&line[start], (index-start), in, out);
			in = "#stdin";
			advance(line, &index, &start);
			ft_lstadd(&instructions, instr);
			instr = ft_lstat(instructions, 0)->content;
			instr->in = find_filename(&line[start]);
			//ft_lstdelat(&instructions, 0, NULL);
			//ft_lstadd_front(&instructions, ft_lstnew(instr));
			index += ft_strlen(instr->in);
			advance(line, &index, &start);
		}
		if (line[index] == '>')
		{
			if (line[index+1] == '>')
				printf("DOUBLE REDIRECT"); //TODO
			instr = instr_create(&line[start], (index-start), in, "");
			in = "#stdin";
			advance(line, &index, &start);
			instr->out = find_filename(&line[start]);
			index += ft_strlen(instr->out);
			ft_lstadd(&instructions, instr);
			advance(line, &index, &start);
		}
		if (line[index] == '|')
		{
			instr = instr_create(&line[start], (index-start), in, "#pipe");
			in = "#pipe";
			ft_lstadd(&instructions, instr);
			advance(line, &index, &start);
		}
		if (line[index] == '#')
		{
			index++;
			while (line[index] != '\n' && line[index] != '\0')
				index++;
		}
		if (line[index] == '\"' || line[index] == '\'')
		{
			quote = line[index];
			index++;
			while (line[index] != quote && line[index] != '\0')
				index++;
			if (line[index] == '\0')
			{
				printf("Syntax error: Unclosed quotes\n");
				printf("find_token\n");
				return (NULL);
			}
		}
		if (line[index] == '\\' || line[index] == ';')
		{
			printf("Syntax error: Unexpected %c\n", line[index]);
			return (NULL);
		}
		index++;
	}
	if (index - start > 1) {
		instr = instr_create(&line[start], (index - start), in, out);
		ft_lstadd(&instructions, instr);
	}
	return (instructions);
}

char	*build_prompt()
{
	char	*prompt;
	char	*cwd;

	cwd = ft_calloc(1, 1024);
	getcwd(cwd, 1024);
	prompt = NULL;
	if (getenv("USER")) {
		ft_strext(&prompt, getenv("USER"), ft_strlen(getenv("USER")));
		ft_strext(&prompt, "@", 1);
	}
	if (ttyname(0)) {
		ft_strext(&prompt, ttyname(0), ft_strlen(ttyname(0)));
		ft_strext(&prompt, ":", 1);
	}
	if (cwd) {
		ft_strext(&prompt, cwd, ft_strlen(cwd));
	}
	ft_strext(&prompt, "$ ", 2);
	free(cwd);
	return (prompt);
}


char	*replace_var(char *line, char **envp)
{
	char	*replaced_line;
	char	*variable_name;
	int		start;
	int		index;
	int		len;

	start = 0;
	index = 0;
	replaced_line = NULL;
	while (line[index] != '\0')
	{
		if (line[index] == '$')
		{
			ft_strext(&replaced_line, &line[start], (index-start));
			index++;
			if (line[index] == '{')
				index++;
			if (ft_isdigit(line[index]))
			{
				printf("Illegal variable name\n");
				return ("");
			}
			len = 0;
			while (line[index+len] != '\0' && (ft_isalnum(line[index+len]) || line[index+len] == '_')) //TODO: underscores and stuff
				len++;
			variable_name = NULL;
			ft_strext(&variable_name, &line[index], len);
			if (!ft_in_envp(envp, variable_name))
			{
				printf("Variable not found: %s\n", variable_name);
				return ("");
			}
			ft_strext(&replaced_line, ft_in_envp(envp, variable_name), ft_strlen(ft_in_envp(envp, variable_name)));
			start = index + ft_strlen(variable_name);
			if (line[start] == '}')
				start++;
			index = start - 1;
		}
		if (line[index] == '\'')
		{
			index++;
			while (line[index] != '\'' && line[index] != '\0')
				index++;
			if (line[index] == '\0')
			{
				printf("Syntax error: Unclosed quotes\n");
				printf("replace_var\n");
				return ("");
			}
			ft_strext(&replaced_line, &line[start], (index-start+1));
			start = index + 1;
		}
		index++;
	}
	ft_strext(&replaced_line, &line[start], (index-start));
	return (replaced_line);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		return;
	}
}

char **replace_arg(char *line)
{
	char	*replaced_arg;
	int		start;
	int		index;
	t_list	*arg_arr;
	char	quote;

	start = 0;
	index = 0;
	arg_arr = NULL;
	replaced_arg = NULL;
	while (line[index] != '\0')
	{
		if (line[index] == '\'' || line[index] ==  '\"')
		{
			quote = line[index];
			index++;
			while (!(line[index] == quote || line[index] == '\0'))
				index++;
			if (line[index] == '\0')
			{
				printf("Syntax error: Unclosed quotes\n");
				printf("replace_arg\n");
				return (NULL);
			}
			start++;
			replaced_arg = ft_substr(line, start, (index-start));
			printf("Replaced String ARG: %s\n", replaced_arg);
			if (ft_strcmp(replaced_arg, ""))
				ft_lstadd(&arg_arr, replaced_arg);
			index++;
			advance(line, &index, &start);
		}
		if (line[index] == ' ') {
			replaced_arg = ft_substr(line, start, (index-start));
			printf("Replaced Command ARG: %s\n", replaced_arg);
			if (ft_strcmp(replaced_arg, ""))
				ft_lstadd(&arg_arr, replaced_arg);
			advance(line, &index, &start);
		}
		index++;
	}
	if (index - start > 1) {
		replaced_arg = ft_substr(line, start, (index-start));
		printf("Replaced Command ARG: %s\n", replaced_arg);
		if (ft_strcmp(replaced_arg, ""))
			ft_lstadd(&arg_arr, replaced_arg);
	}
	return (ft_lsttoarr(arg_arr));
}

char	*find_in_path(char *exec_name, char **envp) {
	char	**paths;
	int		index;
	DIR		*dir;
	struct dirent	*dirinfo;
	char	*full_path;

	full_path = NULL;
	paths = ft_split(ft_in_envp(envp, "PATH"), ':');
	if (!paths)
		return (full_path);
	index = 0;
	while (paths[index] != NULL) {
		//printf("FOLDER: %s\n", paths[index]);
		dir = opendir(paths[index]);
		while (1) {
			dirinfo = readdir(dir);
			if (dirinfo == NULL)
				break ;
			//printf("FILE: %s\n", dirinfo->d_name);
			if (ft_strcmp(dirinfo->d_name, exec_name) == 0)
			{
				printf("Found executable\n");
				full_path = NULL;
				ft_strext(&full_path, paths[index], ft_strlen(paths[index]));
				ft_strext(&full_path, "/", 1);
				ft_strext(&full_path, dirinfo->d_name, ft_strlen(dirinfo->d_name));
				break ;
			}
			if (full_path != NULL)
				break ;
		}
		closedir(dir);
		free(paths[index]);
		index++;
	}
	free(paths);
	return (full_path);
}

void	execute_command(t_list *commands, char **envp)
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
		if (ft_isalpha(arg[0][0])) {
			arg[0] = find_in_path(arg[0], envp);
			if (arg[0] == NULL) {
				printf("Executable not found in PATH\n");
				return ;
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
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*prompt;
	char	*replaced_line;
	t_list	*tokens;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	//ft_printarr(envp);
	while (1 && (argc || !argc) && (argv || !argv))
	{
		prompt = build_prompt();
		data.line = readline(prompt);
		if (!data.line)
			exit(0);
		add_history(data.line);
		replaced_line = replace_var(data.line, envp);
		printf("Replaced line: %s\n", replaced_line);
		tokens = find_token(replaced_line);
		execute_command(tokens, envp);
		free(tokens);
		free(data.line);
		free(prompt);
	}
	return (0);
}

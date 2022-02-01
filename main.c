/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:06:02 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/01 17:11:48 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void del(void *content)
{
	t_instruction *instr;

	instr = (t_instruction *)content;
	free(instr->command);
	free(instr);
}

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
			{
				if (parts[1])
					value = ft_strdup(parts[1]);
			}
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
	return (filename);
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
	char	*text;

	start = 0;
	index = 0;
	instructions = NULL;
	in = "#stdin";
	out = "#stdout";
	while (line[index] != '\0')
	{
		if (line[index] == '<')
		{
			instr = instr_create(&line[start], (index-start), in, out);
			in = "#stdin";
			ft_lstadd(&instructions, instr);
			advance(line, &index, &start);
			instr = ft_lstat(instructions, 0)->content;
			if (line[index+1] == '<')
			{
				index++;
				start++;
				instr->in = ft_strdup("#text");
				while (1)
				{
					text = readline("");
					if (!text || ft_strcmp(text, find_filename(&line[start])) == 0){
						break ;
					}
					ft_strext(&(instr->in), text, ft_strlen(text));
					ft_strext(&(instr->in), "\n", 1);
					free(text);
				}
			}
			else
			{
				instr->in = find_filename(&line[start]);
			}
			ft_print(instr->in);
			index += ft_strlen(find_filename(&line[start]));
			advance(line, &index, &start);
		}
		if (line[index] == '>')
		{
			instr = instr_create(&line[start], (index-start), in, "");
			in = "#stdin";
			advance(line, &index, &start);
			if (line[index+1] == '>')
			{
				start++;
				index++;
				text = ft_strdup("#append");
				ft_strext(&text, find_filename(&line[start]), ft_strlen(find_filename(&line[start])));
				instr->out = text;
			}
			else
				instr->out = find_filename(&line[start]);
			index += ft_strlen(find_filename(&line[start]));
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
			instr = instr_create(&line[start], (index-start), in, out);
			in = "#stdin";
			ft_lstadd(&instructions, instr);
			advance(line, &index, &start);
			index++;
			while (line[index] != '\n' && line[index] != '\0')
				index++;
			start = index + 1;
		}
		if (line[index] == '\"' || line[index] == '\'')
		{
			quote = line[index];
			index++;
			while (line[index] != quote && line[index] != '\0')
				index++;
			if (line[index] == '\0')
			{
				ft_putstr_fd("Syntax error: Unclosed quotes\n", 2);
				return (NULL);
			}
		}
		if (line[index] == '\\' || line[index] == ';')
		{
			ft_putstr_fd("Syntax error: Unexpected ", 2);
			ft_putchar_fd(line[index], 2);
			ft_putstr_fd("\n", 2);
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

char	*replace_var(char *line, char **envp, int returncode)
{
	char	*replaced_line;
	char	*variable_name;
	char	*value;
	int		start;
	int		index;
	int		len;

	start = 0;
	index = 0;
	replaced_line = ft_strdup("");
	while (line[index] != '\0')
	{
		if (line[index] == '$')
		{
			ft_strext(&replaced_line, &line[start], (index-start));
			index++;
			if (line[index] == '{')
				index++;
			if (line[index] == '?')
			{
				ft_strext(&replaced_line, ft_itoa(returncode), ft_strlen(ft_itoa(returncode)));
				start = index + 1;
				if (line[start] == '}')
					start++;
				index = start;
				continue;
			}
			if (ft_isdigit(line[index]))
			{
				ft_putstr_fd("Illegal variable name\n", 2);
				free(replaced_line);
				return (ft_strdup(""));
			}
			len = 0;
			while (line[index+len] != '\0' && (ft_isalnum(line[index+len]) || line[index+len] == '_')) //TODO: underscores and stuff
				len++;
			variable_name = NULL;
			ft_strext(&variable_name, &line[index], len);
			value = ft_in_envp(envp, variable_name);
			if (value)
			{
				ft_strext(&replaced_line, value, ft_strlen(value));
				free(value);
			}
			start = index + ft_strlen(variable_name);
			if (line[start] == '}')
				start++;
			index = start - 1;
			free(variable_name);
		}
		if (line[index] == '\'')
		{
			index++;
			while (line[index] != '\'' && line[index] != '\0')
				index++;
			if (line[index] == '\0')
			{
				ft_putstr_fd("Syntax error: Unclosed quotes\n", 2);
				free(replaced_line);
				return (ft_strdup(""));
			}
			ft_strext(&replaced_line, &line[start], (index-start+1));
			start = index + 1;
		}
		index++;
	}
	ft_strext(&replaced_line, &line[start], (index-start));
	return (replaced_line);
}

char **replace_arg(char *line)
{
	char	*replaced_arg;
	int		start;
	int		index;
	t_list	*arg_arr;
	char	quote;
	char	**output;

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
				ft_putstr_fd("Syntax error: Unclosed quotes\n", 2);
				ft_lstclear(&arg_arr, free);
				return (NULL);
			}
			start++;
			replaced_arg = ft_substr(line, start, (index-start));
			if (ft_strcmp(replaced_arg, ""))
				ft_lstadd(&arg_arr, replaced_arg);
			index++;
			advance(line, &index, &start);
		}
		if (line[index] == ' ') {
			replaced_arg = ft_substr(line, start, (index-start));
			if (ft_strcmp(replaced_arg, ""))
				ft_lstadd(&arg_arr, replaced_arg);
			advance(line, &index, &start);
		}
		index++;
	}
	if (index - start > 0) {
		replaced_arg = ft_substr(line, start, (index-start));
		if (ft_strcmp(replaced_arg, ""))
			ft_lstadd(&arg_arr, replaced_arg);
	}
	output = ft_lsttoarr(arg_arr);
	ft_lstclear(&arg_arr, free);
	return (output);
}

char	*find_in_path(char *exec_name, char **envp) {
	char	**paths;
	int		index;
	DIR		*dir;
	struct dirent	*dirinfo;
	char	*full_path;
	char	*value;

	full_path = NULL;
	value = ft_in_envp(envp, "PATH");
	if (!value)
		return (full_path);
	paths = ft_split(value, ':');
	free(value);
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
		index++;
	}
	ft_arrclear(paths, free);
	return (full_path);
}

int	main(int argc, char **argv, char **input_envp)
{
	t_data	data;
	char	*prompt;
	char	*replaced_line;
	t_list	*tokens;
	int		returncode;
	char	**envp;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	//ft_printarr(envp);
	returncode = 0;
	envp = ft_arrdup(input_envp);
	while (1 && (argc || !argc) && (argv || !argv))
	{
		prompt = build_prompt();
		data.line = readline(prompt);
		if (!data.line)
			break;
		add_history(data.line);
		replaced_line = replace_var(data.line, envp, returncode);
		tokens = find_token(replaced_line);
		free(replaced_line);
		returncode = execute_command(tokens, &envp);
		ft_lstclear(&tokens, del);
		free(data.line);
		free(prompt);
	}
	ft_arrclear(envp, free);
	free(prompt);
	return (0);
}

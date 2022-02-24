/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:06:02 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/24 15:59:36 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del(void *content)
{
	t_instruction	*instr;

	instr = (t_instruction *)content;
	free(instr->command);
	free(instr->in);
	free(instr->out);
	free(instr);
}

char	*ft_in_envp(char **envp, char *variable)
{
	char	**parts;
	char	*value;

	value = NULL;
	while (*envp)
	{
		parts = ft_split(*envp, '=');
		if (parts)
		{
			if (ft_strcmp(parts[0], variable) == 0)
				if (parts[1])
					value = ft_strdup(parts[1]);
			ft_arrclear(parts, free);
		}
		if (value)
			break ;
		envp++;
	}
	return (value);
}

char	*find_fname(char *line)
{
	char	*filename;
	int		writer;
	char	quote;

	while (*line == ' ')
		line++;
	filename = ft_calloc(1, ft_strlen(line) + 1);
	writer = 0;
	quote = '\0';
	while (*line != '\0')
	{
		if (*line == '"' || *line == '\'')
		{
			if (quote == '\0')
				quote = *line;
			else
				quote = '\0';
		}
		else if ((*line == '#' || *line == ' ') && quote == '\0')
			break ;
		else
			filename[writer++] = *line;
		line++;
	}
	return (filename);
}

char	*replace_var(char *line, char **envp, int returncode)
{
	char	*rep_line;
	char	*variable_name;
	char	*value;
	int		start;
	int		index;
	int		len;

	start = 0;
	index = 0;
	rep_line = ft_strdup("");
	while (line[index] != '\0')
	{
		if (line[index] == '$')
		{
			ft_strext(&rep_line, &line[start], (index - start));
			index++;
			if (line[index] == '{')
				index++;
			if (line[index] == '?')
			{
				value = ft_itoa(returncode);
				if (value)
				{
					ft_strext(&rep_line, value, ft_strlen(value));
					free(value);
				}
				start = index + 1;
				if (line[start] == '}')
					start++;
				index = start;
				continue ;
			}
			if (ft_isdigit(line[index]))
			{
				ft_putstr_fd("Illegal variable name\n", 2);
				free(rep_line);
				return (ft_strdup(""));
			}
			len = 0;
			while (line[index + len] != '\0' && (ft_isalnum(line[index + len]) || line[index + len] == '_'))
				len++;
			variable_name = NULL;
			ft_strext(&variable_name, &line[index], len);
			value = ft_in_envp(envp, variable_name);
			if (value)
			{
				ft_strext(&rep_line, value, ft_strlen(value));
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
				free(rep_line);
				return (ft_strdup(""));
			}
			ft_strext(&rep_line, &line[start], (index - start + 1));
			start = index + 1;
		}
		index++;
	}
	ft_strext(&rep_line, &line[start], (index - start));
	return (rep_line);
}

char	**replace_arg(char *line)
{
	char	*replaced_arg;
	int		start;
	int		index;
	t_list	*arg_arr;
	char	quote;
	char	**output;
	int		is_quoted;

	start = 0;
	index = 0;
	arg_arr = NULL;
	replaced_arg = NULL;
	is_quoted = 0;
	quote = '"';
	while (1)
	{
		if (((line[index] == '\'' || line[index] == '\"') && !is_quoted) || (line[index] == quote && is_quoted))
		{
			replaced_arg = ft_strext(&replaced_arg, &line[start], (index - start));
			quote = line[index];
			is_quoted = !is_quoted;
			start = index + 1;
		}
		if (line[index] == ' ' && !is_quoted)
		{
			replaced_arg = ft_strext(&replaced_arg, &line[start], (index - start));
			if (ft_strcmp(replaced_arg, "") != 0)
			{
				ft_lstadd(&arg_arr, replaced_arg);
				replaced_arg = NULL;
			}
			advance(line, &index, &start);
		}
		if (line[index] == '\0')
		{
			if (is_quoted)
			{
				ft_putstr_fd("Error: Unclosed quotes", 2);
				if (replaced_arg)
					free(replaced_arg);
				ft_lstclear(&arg_arr, free);
				return (NULL);
			}
			replaced_arg = ft_strext(&replaced_arg, &line[start], (index - start));
			if (ft_strcmp(replaced_arg, "") != 0)
				ft_lstadd(&arg_arr, replaced_arg);
			else
				free(replaced_arg);
			break ;
		}
		index++;
	}
	output = ft_lsttoarr(arg_arr);
	ft_lstclear(&arg_arr, free);
	return (output);
}

char	*find_in_path(char *exec_name, char **envp)
{
	char			**paths;
	int				index;
	DIR				*dir;
	struct dirent	*dirinfo;
	char			*full_path;
	char			*value;

	full_path = NULL;
	value = ft_in_envp(envp, "PATH");
	if (!value)
		return (full_path);
	paths = ft_split(value, ':');
	free(value);
	if (!paths)
		return (full_path);
	index = 0;
	while (paths[index] != NULL)
	{
		dir = opendir(paths[index]);
		while (dir)
		{
			dirinfo = readdir(dir);
			if (dirinfo == NULL)
				break ;
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
		if (dir)
			closedir(dir);
		index++;
	}
	ft_arrclear(paths, free);
	return (full_path);
}

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

int	main(int argc, char **argv, char **input_envp)
{
	t_data	data;
	char	*rep_line;
	t_list	*tokens;
	int		returncode;
	char	**envp;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	returncode = 0;
	envp = ft_arrdup(input_envp);
	update_pwd(&envp);
	while (returncode < 256 && (argc || !argc) && (argv || !argv))
	{
		data.prompt = build_prompt();
		data.line = readline(data.prompt);
		free(data.prompt);
		if (!data.line)
			break ;
		add_history(data.line);
		rep_line = replace_var(data.line, envp, returncode);
		tokens = find_token(rep_line);
		free(rep_line);
		returncode = execute_command(tokens, &envp, returncode);
		ft_lstclear(&tokens, del);
		free(data.line);
	}
	ft_arrclear(envp, free);
	return (returncode - 256);
}

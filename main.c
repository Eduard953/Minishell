/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:06:02 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/24 17:35:30 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_int	n;

	init_ints(&n);
	rep_line = ft_strdup("");
	while (line[n.idx] != '\0')
	{
		if (line[n.idx] == '$')
		{
			ft_strext(&rep_line, &line[n.start], (n.idx - n.start));
			n.idx++;
			if (line[n.idx] == '{')
				n.idx++;
			if (line[n.idx] == '?')
			{
				value = ft_itoa(returncode);
				if (value)
				{
					ft_strext(&rep_line, value, ft_strlen(value));
					free(value);
				}
				n.start = n.idx + 1;
				if (line[n.start] == '}')
					n.start++;
				n.idx = n.start;
				continue ;
			}
			if (ft_isdigit(line[n.idx]))
			{
				ft_putstr_fd("Illegal variable name\n", 2);
				free(rep_line);
				return (ft_strdup(""));
			}
			while (line[n.idx + n.len] != '\0' && (ft_isalnum(line[n.idx + n.len]) || line[n.idx + n.len] == '_'))
				n.len++;
			variable_name = NULL;
			ft_strext(&variable_name, &line[n.idx], n.len);
			value = ft_in_envp(envp, variable_name);
			if (value)
			{
				ft_strext(&rep_line, value, ft_strlen(value));
				free(value);
			}
			n.start = n.idx + ft_strlen(variable_name);
			if (line[n.start] == '}')
				n.start++;
			n.idx = n.start - 1;
			free(variable_name);
		}
		if (line[n.idx] == '\'')
		{
			n.idx++;
			while (line[n.idx] != '\'' && line[n.idx] != '\0')
				n.idx++;
			if (line[n.idx] == '\0')
			{
				ft_putstr_fd("Syntax error: Unclosed quotes\n", 2);
				free(rep_line);
				return (ft_strdup(""));
			}
			ft_strext(&rep_line, &line[n.start], (n.idx - n.start + 1));
			n.start = n.idx + 1;
		}
		n.idx++;
	}
	ft_strext(&rep_line, &line[n.start], (n.idx - n.start));
	return (rep_line);
}

char	*find_in_path(char *exec_name, char **envp)
{
	char			**paths;
	int				idx;
	DIR				*dir;
	struct dirent	*dirinfo;
	char			*f_path;
	char			*value;

	f_path = NULL;
	value = ft_in_envp(envp, "PATH");
	if (!value)
		return (f_path);
	paths = ft_split(value, ':');
	free(value);
	if (!paths)
		return (f_path);
	idx = 0;
	while (paths[idx] != NULL)
	{
		dir = opendir(paths[idx]);
		while (dir)
		{
			dirinfo = readdir(dir);
			if (dirinfo == NULL)
				break ;
			if (ft_strcmp(dirinfo->d_name, exec_name) == 0)
			{
				f_path = NULL;
				ft_strext(&f_path, paths[idx], ft_strlen(paths[idx]));
				ft_strext(&f_path, "/", 1);
				ft_strext(&f_path, dirinfo->d_name, ft_strlen(dirinfo->d_name));
				break ;
			}
			if (f_path != NULL)
				break ;
		}
		if (dir)
			closedir(dir);
		idx++;
	}
	ft_arrclear(paths, free);
	return (f_path);
}

int	main(int argc, char **argv, char **input_envp)
{
	t_data	data;
	char	**envp;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	data.returncode = 0;
	envp = ft_arrdup(input_envp);
	update_pwd(&envp);
	while (data.returncode < 256 && (argc || !argc) && (argv || !argv))
	{
		data.prompt = build_prompt();
		data.line = readline(data.prompt);
		free(data.prompt);
		if (!data.line)
			break ;
		add_history(data.line);
		data.rep_line = replace_var(data.line, envp, data.returncode);
		data.tokens = find_token(data.rep_line);
		free(data.rep_line);
		data.returncode = execute_command(data.tokens, &envp, data.returncode);
		ft_lstclear(&data.tokens, del);
		free(data.line);
	}
	ft_arrclear(envp, free);
	return (data.returncode - 256);
}

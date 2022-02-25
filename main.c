/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:06:02 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/25 16:27:02 by pstengl          ###   ########.fr       */
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
		else if (ft_isoneof(*line, "# <>|;") && quote == '\0')
			break ;
		else
			filename[writer++] = *line;
		line++;
	}
	return (filename);
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

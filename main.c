/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:06:02 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/16 16:50:46 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

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
			instr = instr_create(&line[start], (index-start), "", out);
			in = "#stdin";
			advance(line, &index, &start);
			instr->in = find_filename(&line[start]);
			index += ft_strlen(instr->out);
			ft_lstadd(&instructions, instr);
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
		if (line[index] == '"' || line[index] == '\'')
		{
			index++;
			while (line[index] != '"' && line[index] != '\'' && line[index] != '\0')
				index++;
			if (line[index] == '\0')
			{
				printf("Syntax error: Unclosed quotes\n");
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
	ft_strext(&prompt, getenv("USER"), ft_strlen(getenv("USER")));
	ft_strext(&prompt, "@", 1);
	ft_strext(&prompt, ttyname(0), ft_strlen(ttyname(0)));
	ft_strext(&prompt, ":", 1);
	ft_strext(&prompt, cwd, ft_strlen(cwd));
	ft_strext(&prompt, "$ ", 2);
	free(cwd);
	return (prompt);
}

char	*replace_var(char *line)
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
			if (!getenv(variable_name))
			{
				printf("Variable not found: %s\n", variable_name);
				return ("");
			}
			ft_strext(&replaced_line, getenv(variable_name), ft_strlen(getenv(variable_name)));
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
				return ("");
			}
			start = index;
		}
		index++;
	}
	ft_strext(&replaced_line, line+start, (index-start));
	return (replaced_line);
}

int	main()
{
	t_data	data;
	char	*prompt;
	char	*replaced_line;

	prompt = build_prompt();
	while (1)
	{
		data.line = readline(prompt);
		if (!data.line)
			exit(-1);
		add_history(data.line);
		replaced_line = replace_var(data.line);
		printf("Replaced line: %s\n", replaced_line);
		find_token(replaced_line);
		free(data.line);
	}
	free(prompt);
	return (0);
}

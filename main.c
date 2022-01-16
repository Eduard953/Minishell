/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:06:02 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/16 15:40:35 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./libft/libft.h"

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

int	main()
{
	t_data	data;

	while (1)
	{
		data.line = readline("shell:>$ ");
		if (!data.line)
			exit(-1);
		add_history(data.line);
		// Replace Variables //TODO
		find_token(data.line);
		free(data.line);
	}
	return (0);
}

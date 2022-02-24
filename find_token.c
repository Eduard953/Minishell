/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:03:08 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/24 13:20:29 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	red_left(char **in, char *line, int length, t_list **instructions)
{
	t_instruction	*instr;

	instr = instr_create(line, length, *in, "#stdout");
	*in = "#stdin";
	ft_lstadd(instructions, instr);
	instr = ft_lstat(*instructions, 0)->content;
	line += length + 1;
	free(instr->in);
	if (*line == '<')
	{
		line++;
		instr->in = ft_strdup("#text");
		while (1)
		{
			instr->text = readline("");
			if (!instr->text || ft_strcmp(instr->text, find_fname(line)) == 0)
				break ;
			ft_strext(&(instr->in), instr->text, ft_strlen(instr->text));
			ft_strext(&(instr->in), "\n", 1);
			free(instr->text);
		}
	}
	else
		instr->in = find_fname(line);
	return (ft_freestrlen(find_fname(line), free) + 1);
}

int	red_right(char **in, char *line, int length, t_list **instructions)
{
	t_instruction	*instr;
	char			*fname;

	instr = instr_create(line, length, *in, "");
	*in = "#stdin";
	line += length + 1;
	free(instr->out);
	if (*line == '>')
	{
		line++;
		instr->text = ft_strdup("#append");
		fname = find_fname(line);
		ft_strext(&instr->text, fname, ft_strlen(fname));
		free(fname);
		instr->out = instr->text;
	}
	else
		instr->out = find_fname(line);
	ft_lstadd(instructions, instr);
	return (ft_freestrlen(find_fname(line), free) + 1);
}

t_list	*find_token(char *line)
{
	int				start;
	int				index;
	char			*in;
	t_instruction	*instr;
	t_list			*instructions;
	char			quote;

	start = 0;
	index = 0;
	instructions = NULL;
	in = "#stdin";
	while (line[index] != '\0')
	{
		if (line[index] == '<')
		{
			index += red_left(&in, &line[start], (index - start), &instructions);
			start = index + 1;
		}
		if (line[index] == '>')
		{
			index += red_right(&in, &line[start], (index - start), &instructions);
			start = index + 1;
		}
		if (line[index] == '|')
		{
			instr = instr_create(&line[start], (index - start), in, "#pipe");
			in = "#pipe";
			ft_lstadd(&instructions, instr);
			advance(line, &index, &start);
		}
		if (line[index] == '#')
		{
			instr = instr_create(&line[start], (index - start), in, "#stdout");
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
	if (index - start > 1)
	{
		instr = instr_create(&line[start], (index - start), in, "#stdout");
		ft_lstadd(&instructions, instr);
	}
	return (instructions);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:03:08 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/07 15:39:12 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_left(char *in, char *line, int length, t_list *instructions)
{
	t_instruction	*instr;

	instr = instr_create(line, length, in, "#stdout");
	in = "#stdin";
	ft_lstadd(&instructions, instr);
	instr = ft_lstat(instructions, 0)->content;
	line += length + 1;
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
	ft_print(instr->in);
	return (ft_strlen(find_fname(line)));
}

int	redirection_right(char *in, char *line, int length, t_list *instructions)
{
	t_instruction	*instr;

	instr = instr_create(line, length, in, "");
	in = "#stdin";
	line += length;
	if (*line == '>')
	{
		line++;
		instr->text = ft_strdup("#append");
		ft_strext(&instr->text, find_fname(line), ft_strlen(find_fname(line)));
		instr->out = instr->text;
	}
	else
		instr->out = find_fname(line);
	ft_lstadd(&instructions, instr);
	return (ft_strlen(find_fname(line)));
}

t_list	*find_token(char *line)
{
	int				start;
	int				index;
	char			*in;
	char			*out;
	t_instruction	*instr;
	t_list			*instructions;
	char			quote;

	start = 0;
	index = 0;
	instructions = NULL;
	in = "#stdin";
	out = "#stdout";
	while (line[index] != '\0')
	{
		if (line[index] == '<')
		{
			index += redirection_left(in, &line[start], (index - start), instructions);
			start = index + 1;
		}
		if (line[index] == '>')
		{
			index += redirection_right(in, &line[start], (index - start), instructions);
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
			instr = instr_create(&line[start], (index - start), in, out);
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
		instr = instr_create(&line[start], (index - start), in, out);
		ft_lstadd(&instructions, instr);
	}
	return (instructions);
}

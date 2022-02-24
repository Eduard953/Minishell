/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:03:08 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/24 17:12:09 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_instruction	*newxt_instr(char *line, int length,
		t_list **instructions, char *in)
{
	t_instruction	*instr;

	if (length > 1)
	{
		instr = instr_create(line, length, in, "#stdout");
		ft_lstadd(instructions, instr);
	}
	else
		instr = ft_lstat(*instructions, -1)->content;
	return (instr);
}

char	*gather_text(char *fname)
{
	char	*buffer;
	char	*output;

	output = ft_strdup("#text");
	while (1)
	{
		buffer = readline("> ");
		if (!buffer || ft_strcmp(buffer, fname) == 0)
		{
			free(buffer);
			break ;
		}
		ft_strext(&output, buffer, ft_strlen(buffer));
		ft_strext(&output, "\n", 1);
		free(buffer);
	}
	return (output);
}

int	red_left(char *line, int length, t_list **instructions)
{
	t_instruction	*instr;
	char			*fname;

	instr = newxt_instr(line, length, instructions, "");
	line += length + 1;
	free(instr->in);
	if (*line == '<')
	{
		line++;
		fname = find_fname(line);
		instr->in = gather_text(fname);
		free(fname);
	}
	else
		instr->in = find_fname(line);
	return (ft_freestrlen(find_fname(line), free) + 2);
}

int	red_right(char **in, char *line, int length, t_list **instructions)
{
	t_instruction	*instr;
	char			*fname;

	instr = newxt_instr(line, length, instructions, *in);
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
	return (ft_freestrlen(find_fname(line), free) + 2);
}

t_list	*find_token(char *line)
{
	int				length;
	char			*in;
	t_list			*instructions;

	instructions = NULL;
	in = "#stdin";
	length = 0;
	while (line[length] != '\0')
	{
		handle_pipe(&instructions, &in, &line, &length);
		handle_inred(&instructions, &in, &line, &length);
		handle_outred(&instructions, &in, &line, &length);
		if (handle_quotes(&line, &length))
			return (NULL);
		if (handle_forbidden(&line, &length))
			return (NULL);
		if (line[length] == '#')
			break ;
		length++;
	}
	if (length > 1)
		ft_lstadd(&instructions, instr_create(line, length, in, "#stdout"));
	return (instructions);
}

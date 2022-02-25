/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:11:43 by pstengl           #+#    #+#             */
/*   Updated: 2022/02/25 16:08:40 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_list **instructions, char **in, char **line, int *length)
{
	t_instruction	*instr;

	if ((*line)[*length] != '|')
		return ;
	if (*length <= 1)
	{
		instr = ft_lstat(*instructions, -1)->content;
		if (strcmp(instr->out, "#stdout") == 0)
		{
			instr->out = ft_strdup("#pipe");
			*in = "#pipe";
		}
		else
			*in = "#text";
	}
	else
	{
		instr = instr_create(*line, *length, *in, "#pipe");
		ft_lstadd(instructions, instr);
		*in = "#pipe";
	}
	*line += *length + 1;
	skip_spaces(line);
	*length = -1;
}

void	handle_inred(t_list **instructions, char **in, char **line, int *length)
{
	if ((*line)[*length] != '<')
		return ;
	(*line) += red_left(line, *length, instructions);
	*in = "#stdin";
	skip_spaces(line);
	*length = -1;
}

void	handle_outred(t_list **instructions, char **in, char **line,
		int *length)
{
	if ((*line)[*length] != '>')
		return ;
	(*line) += red_right(in, line, *length, instructions);
	skip_spaces(line);
	*length = -1;
}

int	handle_quotes(char **line, int *length)
{
	char			quote;

	if ((*line)[*length] != '"' && (*line)[*length] != '\'')
		return (0);
	quote = (*line)[*length];
	(*length)++;
	while ((*line)[*length] != quote && (*line)[*length] != '\0')
		(*length)++;
	if ((*line)[*length] == '\0')
	{
		ft_putstr_fd("Syntax error: Unclosed quotes\n", 2);
		return (1);
	}
	return (0);
}

int	handle_forbidden(char **line, int *length)
{
	if ((*line)[*length] != '\\' && (*line)[*length] != ';')
		return (0);
	ft_putstr_fd("Syntax error: Unexpected ", 2);
	ft_putchar_fd((*line)[*length], 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

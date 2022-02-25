/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:11:43 by pstengl           #+#    #+#             */
/*   Updated: 2022/02/25 13:42:41 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_list **instructions, char **in, char **line, int *length)
{
	t_instruction	*instr;

	if ((*line)[*length] != '|')
		return ;
	if (*length > 1)
	{
		instr = instr_create(*line, *length, *in, "#pipe");
		ft_lstadd(instructions, instr);
		*in = "#pipe";
	}
	else
		*in = "#text";
	*line += *length + 1;
	*length = 0;
}

void	handle_inred(t_list **instructions, char **in, char **line, int *length)
{
	if ((*line)[*length] != '<')
		return ;
	*length += red_left(*line, *length, instructions);
	*in = "#stdin";
	*line += *length + 1;
}

void	handle_outred(t_list **instructions, char **in, char **line,
		int *length)
{
	if ((*line)[*length] != '>')
		return ;
	*length += red_right(in, *line, *length, instructions);
	*line += *length + 1;
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

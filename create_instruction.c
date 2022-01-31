/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_instruction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:23:09 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/31 14:29:34 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (instr);
}

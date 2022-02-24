/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:17:30 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/24 17:35:56 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	t_instruction	*instr;

	instr = (t_instruction *)content;
	free(instr->command);
	free(instr->in);
	free(instr->out);
	free(instr);
}

void	init_ints(t_int *n)
{
	n->idx = 0;
	n->is_q = 0;
	n->len = 0;
	n->start = 0;
}

int	ft_checkname(char *name)
{
	if (ft_isdigit(name[0]) || (ft_strlen(name) < 1))
		return (0);
	while (*name)
	{
		if (!(ft_isalnum(*name) || (*name == '_')))
			return (0);
		name++;
	}
	return (1);
}

void	advance(char *line, int *index, int *start)
{
	if (line[*index] == '\0')
	{
		(*index)--;
		*start = (*index) + 1;
		return ;
	}
	*start = (*index) + 1;
	while (line[*start] == ' ')
		(*start)++;
	*index = (*start) - 1;
}

char	*ft_in_envp(char **envp, char *variable)
{
	char	**parts;
	char	*value;

	value = NULL;
	while (*envp)
	{
		parts = ft_split(*envp, '=');
		if (parts)
		{
			if (ft_strcmp(parts[0], variable) == 0)
				if (parts[1])
					value = ft_strdup(parts[1]);
			ft_arrclear(parts, free);
		}
		if (value)
			break ;
		envp++;
	}
	return (value);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:17:30 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/24 13:35:44 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

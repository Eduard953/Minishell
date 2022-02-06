/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:17:30 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/06 15:22:54 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

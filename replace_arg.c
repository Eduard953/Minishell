/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:13:49 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/25 15:17:28 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	endloop(t_int n, char **rep_arg, t_list **arg_arr, char *line)
{
	if (n.is_q)
	{
		ft_putstr_fd("Error: Unclosed quotes", 2);
		if (*rep_arg)
			free(*rep_arg);
		ft_lstclear(arg_arr, free);
		return (1);
	}
	*rep_arg = ft_strext(rep_arg, &line[n.start], (n.idx - n.start));
	if (ft_strcmp(*rep_arg, "") != 0)
		ft_lstadd(arg_arr, *rep_arg);
	else
		free(*rep_arg);
	return (0);
}

void	do_this(t_int *n, t_list **arg_arr, char **rep_arg, char *line)
{
	if (((line[n->idx] == '\'' || line[n->idx] == '\"') && !n->is_q)
		|| (line[n->idx] == n->quote && n->is_q))
	{
		*rep_arg = ft_strext(rep_arg, &line[n->start], (n->idx - n->start));
		n->quote = line[n->idx];
		n->is_q = !n->is_q;
		n->start = n->idx + 1;
	}
	if (line[n->idx] == ' ' && !n->is_q)
	{
		*rep_arg = ft_strext(rep_arg, &line[n->start], (n->idx - n->start));
		if (ft_strcmp(*rep_arg, "") != 0)
		{
			ft_lstadd(arg_arr, *rep_arg);
			*rep_arg = NULL;
		}
		advance(line, &n->idx, &n->start);
	}
}

char	**replace_arg(char *line)
{
	char	*rep_arg;
	t_int	n;
	t_list	*arg_arr;
	char	**output;

	init_ints(&n);
	arg_arr = NULL;
	rep_arg = NULL;
	while (1)
	{
		do_this(&n, &arg_arr, &rep_arg, line);
		if (line[n.idx] == '\0')
		{
			if (endloop(n, &rep_arg, &arg_arr, line))
				return (NULL);
			break ;
		}
		n.idx++;
	}
	output = ft_lsttoarr(arg_arr);
	ft_lstclear(&arg_arr, free);
	return (output);
}

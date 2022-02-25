/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:34:53 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/25 16:08:50 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	help2(t_int *n, char *line, char **rep_line, int returncode)
{
	char	*value;

	ft_strext(rep_line, &line[n->start], (n->idx - n->start));
	n->idx++;
	if (line[n->idx] == '{')
		n->idx++;
	if (line[n->idx] == '?')
	{
		value = ft_itoa(returncode);
		if (value)
		{
			ft_strext(rep_line, value, ft_strlen(value));
			free(value);
		}
		n->start = n->idx + 1;
		if (line[n->start] == '}')
			n->start++;
		n->idx = n->start;
		return (1);
	}
	return (0);
}

void	help3(t_int *n, char *line, char **envp, char **rep_line)
{
	char	*variable_name;
	char	*value;

	while (line[n->idx + n->len] != '\0' && (ft_isalnum(line[n->idx + n->len])
			|| line[n->idx + n->len] == '_'))
		n->len++;
	variable_name = NULL;
	ft_strext(&variable_name, &line[n->idx], n->len);
	value = ft_in_envp(envp, variable_name);
	if (value)
	{
		ft_strext(rep_line, value, ft_strlen(value));
		free(value);
	}
	n->start = n->idx + ft_strlen(variable_name);
	if (line[n->start] == '}')
		n->start++;
	n->idx = n->start - 1;
	free(variable_name);
}

int	help4(t_int *n, char *line, char **rep_line)
{
	n->idx++;
	while (line[n->idx] != '\'' && line[n->idx] != '\0')
		n->idx++;
	if (line[n->idx] == '\0')
	{
		ft_putstr_fd("Syntax error: Unclosed quotes\n", 2);
		free(*rep_line);
		return (1);
	}
	ft_strext(rep_line, &line[n->start], (n->idx - n->start + 1));
	n->start = n->idx + 1;
	return (0);
}

char	*replace_var(char *line, char **envp, int returncode)
{
	char	*rep_line;
	t_int	n;

	init_ints(&n);
	rep_line = ft_strdup("");
	while (line[n.idx] != '\0')
	{
		if (line[n.idx] == '$')
		{
			if (help2(&n, line, &rep_line, returncode))
				continue ;
			if (ft_isdigit(line[n.idx]))
			{
				ft_putstr_fd("Illegal variable name\n", 2);
				free(rep_line);
				return (ft_strdup(""));
			}
			help3(&n, line, envp, &rep_line);
		}
		if (line[n.idx] == '\'' && help4(&n, line, &rep_line))
			return (ft_strdup(""));
		n.idx++;
	}
	ft_strext(&rep_line, &line[n.start], (n.idx - n.start));
	return (rep_line);
}

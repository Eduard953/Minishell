/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:34:53 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/25 15:35:12 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_var(char *line, char **envp, int returncode)
{
	char	*rep_line;
	char	*variable_name;
	char	*value;
	t_int	n;

	init_ints(&n);
	rep_line = ft_strdup("");
	while (line[n.idx] != '\0')
	{
		if (line[n.idx] == '$')
		{
			ft_strext(&rep_line, &line[n.start], (n.idx - n.start));
			n.idx++;
			if (line[n.idx] == '{')
				n.idx++;
			if (line[n.idx] == '?')
			{
				value = ft_itoa(returncode);
				if (value)
				{
					ft_strext(&rep_line, value, ft_strlen(value));
					free(value);
				}
				n.start = n.idx + 1;
				if (line[n.start] == '}')
					n.start++;
				n.idx = n.start;
				continue ;
			}
			if (ft_isdigit(line[n.idx]))
			{
				ft_putstr_fd("Illegal variable name\n", 2);
				free(rep_line);
				return (ft_strdup(""));
			}
			while (line[n.idx + n.len] != '\0' && (ft_isalnum(line[n.idx + n.len]) || line[n.idx + n.len] == '_'))
				n.len++;
			variable_name = NULL;
			ft_strext(&variable_name, &line[n.idx], n.len);
			value = ft_in_envp(envp, variable_name);
			if (value)
			{
				ft_strext(&rep_line, value, ft_strlen(value));
				free(value);
			}
			n.start = n.idx + ft_strlen(variable_name);
			if (line[n.start] == '}')
				n.start++;
			n.idx = n.start - 1;
			free(variable_name);
		}
		if (line[n.idx] == '\'')
		{
			n.idx++;
			while (line[n.idx] != '\'' && line[n.idx] != '\0')
				n.idx++;
			if (line[n.idx] == '\0')
			{
				ft_putstr_fd("Syntax error: Unclosed quotes\n", 2);
				free(rep_line);
				return (ft_strdup(""));
			}
			ft_strext(&rep_line, &line[n.start], (n.idx - n.start + 1));
			n.start = n.idx + 1;
		}
		n.idx++;
	}
	ft_strext(&rep_line, &line[n.start], (n.idx - n.start));
	return (rep_line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:26:40 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/06 15:42:59 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(char **arg, char ***envp)
{
	char	**temp;
	char	**tokens;
	char	*value;
	int		i;

	tokens = ft_split(arg[1], '=');
	value = ft_in_envp(*envp, tokens[0]);
	if (value)
	{
		i = 0;
		while ((*envp)[i] != NULL)
		{
			if (ft_strncmp((*envp)[i], arg[1], ft_strlen(tokens[0]) + 1) == 0)
			{
				free((*envp)[i]);
				(*envp)[i] = ft_strdup(arg[1]);
			}
			i++;
		}
		free(value);
		ft_arrclear(tokens, free);
		return (0);
	}
	temp = ft_calloc(ft_arrlen(*envp) + 2, sizeof(char *));
	if (!temp)
		return (error(5));
	temp = ft_memcpy(temp, *envp, sizeof(char *) * ft_arrlen(*envp));
	temp[ft_arrlen(temp)] = ft_strdup(arg[1]);
	free(value);
	free(*envp);
	ft_arrclear(tokens, free);
	*envp = temp;
	return (0);
}

char	**builtin_unset(char **arg, char **envp)
{
	char	**temp;
	int		envplen;
	int		i;
	int		j;

	i = 0;
	j = 0;
	envplen = 0;
	while (envp[envplen] != NULL)
		envplen++;
	temp = ft_calloc(sizeof(char *), (envplen + 2));
	while (envp[i] != NULL)
	{
		if (!(ft_strncmp(envp[i], arg[1], ft_strlen(arg[1]))))
		{
			if (envp[i][ft_strlen(arg[1])] == '=')
				i++;
		}
		if (envp[i] == NULL)
			break ;
		temp[j] = envp[i];
		j++;
		i++;
	}
	free(envp);
	return (temp);
}

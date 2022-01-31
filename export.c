/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:26:40 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/31 13:57:11 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **builtin_export(char **arg, char **envp)
{
	char **temp;
	char **tokens;
	char *value;
	int envplen;
	int i;


	tokens = ft_split(arg[1], '=');
	value = ft_in_envp(envp, tokens[0]);
	envplen = 0;
	while (envp[envplen] != NULL)
		envplen++;
	temp = ft_calloc(sizeof(char *), (envplen + 2));
	i = 0;
	while (envp[i] != NULL)
	{
		if (!(ft_strncmp(envp[i], arg[1], ft_strlen(tokens[0]) + 1)))
			temp[i] = ft_strdup(arg[1]);
		else
			temp[i] = envp[i];
		i++;
	}
	if (!value)
		temp[i] = ft_strdup(arg[1]);
	return (temp);
}

char **builtin_unset(char **arg, char **envp)
{
	char **temp;

	int envplen;
	int i;
	int j;

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
	return (temp);
}

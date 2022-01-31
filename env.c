/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:22:02 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/31 13:55:48 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_env(char **envp)
{
	if (!(*envp))
		return (error(127));
	while(*envp) 
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}

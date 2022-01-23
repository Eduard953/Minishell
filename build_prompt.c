/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_promt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 15:24:16 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/23 15:24:24 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_prompt()
{
	char	*prompt;
	char	*cwd;

	cwd = ft_calloc(1, 1024);
	getcwd(cwd, 1024);
	prompt = NULL;
	if (getenv("USER")) {
		ft_strext(&prompt, getenv("USER"), ft_strlen(getenv("USER")));
		ft_strext(&prompt, "@", 1);
	}
	if (ttyname(0)) {
		ft_strext(&prompt, ttyname(0), ft_strlen(ttyname(0)));
		ft_strext(&prompt, ":", 1);
	}
	if (cwd) {
		ft_strext(&prompt, cwd, ft_strlen(cwd));
	}
	ft_strext(&prompt, "$ ", 2);
	free(cwd);
	return (prompt);
}

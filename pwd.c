/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:00:54 by pstengl           #+#    #+#             */
/*   Updated: 2022/01/31 13:58:25 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtint_pwd(void)
{
	char	*path;

	ft_println("Builtin pwd");
	path = ft_calloc(1024, 1);
	getcwd(path, 1024);
	ft_println(path);
	free(path);
	return (0);
}

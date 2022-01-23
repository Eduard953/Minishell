/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:00:54 by pstengl           #+#    #+#             */
/*   Updated: 2022/01/23 16:04:08 by pstengl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtint_pwd(void)
{
	char	*path;

	ft_println("Builtin pwd");
	path = ft_calloc(1024, 1);
	getcwd(path, 1024);
	ft_println(path);
	free(path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:51:33 by ebeiline          #+#    #+#             */
/*   Updated: 2022/01/31 13:51:44 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error(int errorcode)
{
	ft_putstr_fd(strerror(errorcode), 2);
	ft_putstr_fd("\n", 2);
	return (errorcode);
}

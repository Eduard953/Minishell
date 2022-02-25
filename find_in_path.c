/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:20:06 by ebeiline          #+#    #+#             */
/*   Updated: 2022/02/25 15:33:47 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_func(char *exec_name, char **paths, char *f_path, int idx)
{
	DIR				*dir;
	struct dirent	*dirinfo;

	dir = opendir(paths[idx]);
	while (dir)
	{
		dirinfo = readdir(dir);
		if (dirinfo == NULL)
			break ;
		if (ft_strcmp(dirinfo->d_name, exec_name) == 0)
		{
			f_path = NULL;
			ft_strext(&f_path, paths[idx], ft_strlen(paths[idx]));
			ft_strext(&f_path, "/", 1);
			ft_strext(&f_path, dirinfo->d_name, ft_strlen(dirinfo->d_name));
			break ;
		}
		if (f_path != NULL)
			break ;
	}
	if (dir)
		closedir(dir);
	return (f_path);
}

char	*find_in_path(char *exec_name, char **envp)
{
	char			**paths;
	int				idx;
	char			*f_path;
	char			*value;

	f_path = NULL;
	value = ft_in_envp(envp, "PATH");
	if (!value)
		return (f_path);
	paths = ft_split(value, ':');
	free(value);
	if (!paths)
		return (f_path);
	idx = 0;
	while (paths[idx] != NULL)
	{
		f_path = new_func(exec_name, paths, f_path, idx);
		idx++;
	}
	ft_arrclear(paths, free);
	return (f_path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:18:41 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/15 13:54:22 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**dirs_list;
	char	*path;
	int		i;
	
	if (ft_strchr(cmd, "/"))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
		path_env = get_path_env(envp);
		if (!path_env)
			return (NULL);
		dirs_list = ft_split(path_env, ':');
		if (!dirs_list)
			return (NULL);
		i = 0;
		while (dirs_list[i])
		{
			path = join_path(dirs_list[i], cmd);
			if (access(path, X_OK) == 0)
			{
				free_split(dirs_list);
				return (path);
			}
			free(path);
			i++;
		}
	free_split(dirs_list);
	return (NULL);
}

char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin (dir, "/");
	full = ft_strjoin (tmp, cmd);
	free (tmp);
	return (full);
}

char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_clean_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:00:07 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/08/04 15:44:03 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int numb_pipes, int **pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < numb_pipes)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

void	clean_and_exit_bonus(char **cmd, char *path,
			t_pipex *px, const char *msg)
{
	if (cmd)
		free_split(cmd);
	if (path)
		free(path);
	if (px && px->pipes)
	{
		close_pipes(px->num_pipes, px->pipes);
		free_all(px->num_pipes, px->pipes);
		px->pipes = NULL;
	}
	error_exit(msg);
}

void	close_and_free(t_pipex *px)
{
	if (px && px->pipes)
	{
		close_pipes(px->num_pipes, px->pipes);
		free_all(px->num_pipes, px->pipes);
		px->pipes = NULL;
	}
}

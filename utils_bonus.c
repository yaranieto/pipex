/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:58:46 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/18 13:02:10 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_cmd(int argc, char **argv)
{
	int	num_cmd;

	num_cmd = argc - 3;
	if (argc < 5 )
		return (0);
	return (num_cmd);
}

int	num_pipes(int argc, char **argv)
{
	return (count_cmd(argc, argv) - 1);
}

int	**create_pipes(int num_pipes)
{
	int	**pipes;
	int	i;
	
	i = 0;
	pipes = malloc(sizeof(int *) * num_pipes);
	if (!pipes)
		error_exit();
	while (i < num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			error_exit();
		if (pipe(pipes[i]) == -1)
			error_exit();
		i++;
	}
	if (!pipes)
		error_exit();
	return (pipes);
}

void	wait_all(int num_cmd)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_cmd)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}

void	free_all(int num_pipes, int **pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}


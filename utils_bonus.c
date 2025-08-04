/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:58:46 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/08/04 13:18:48 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_cmd(int argc)
{
	int	num_cmd;

	num_cmd = argc - 3;
	if (argc < 5)
		return (0);
	return (num_cmd);
}

int	num_pipes(int argc)
{
	return (count_cmd(argc) - 1);
}

int	**create_pipes(int num_pipes)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * num_pipes);
	if (!pipes)
		error_exit("Error no pipes");
	while (i < num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			free_all(i, pipes);
			error_exit("Error no pipes");
		}
		if (pipe(pipes[i]) == -1)
		{
			free_all(i + 1, pipes);
			error_exit("Error no pipes");
		}
		i++;
	}
	return (pipes);
}

void	wait_all(int num_cmd)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < num_cmd)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			ft_putstr_fd("Error waiting for child process\n", 2);
			break ;
		}
		i++;
	}
}

void	free_all(int num_pipes, int **pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < num_pipes)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
			pipes[i] = NULL;
		}
		i++;
	}
	free(pipes);
}

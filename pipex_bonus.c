/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:58:24 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/16 21:17:07 by yara             ###   ########.fr       */
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

int	main_bonus(int argc, char **argv, char **envp)
{
	int		num_cmd;
	int 	num_pipes;
	int		**pipes;
	int 	i;
	pid_t	pid;

	num_cmd = count_cmd(argc, argv);
	num_pipes = num_pipes(argc, argv);
	pipes = create_pipes(num_pipes);
	i = 0;
	if (argc < 5)
		error_exit();
	while (i < num_cmd)
	{
		pid = fork();
		if (pid == -1)
			error_exit();
		if (pid == 0)
			child_process_bonus();
		i++;
	}
	close_pipes();
	wait_all();
	free_all();
	return (0);
}

void	close_pipes(int	num_pipes, int	**pipes)
{

}
void	wait_all(int num_cmd)
{

}
void	execute_all(int argc, char **argv, char **envp, int **pipes)
{
	
}
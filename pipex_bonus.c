/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:58:24 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/17 17:23:21 by ynieto-s         ###   ########.fr       */
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
	int 	numb_pipes;
	int		**pipes;
	int 	i;
	pid_t	pid;

	num_cmd = count_cmd(argc, argv);
	numb_pipes = num_pipes(argc, argv);
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
	close_pipes(num_pipes, pipes);
	wait_all(num_cmd);
	free_all(num_pipes, pipes);
	return (0);
}

void	close_pipes(int	num_pipes, int	**pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
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
void	execute_all(int argc, char **argv, char **envp, int **pipes)
{
	int		numb_pipes;
	int		num_cmd;
	int		i;
	pid_t	pid;

	i = 0;
	num_cmd = count_cmd(argc, argv);
	numb_pipes = num_pipes(argc, argv);
	create_pipes(num_pipes);
	while (i < num_cmd)
	{
		pid = fork();
		if (pid == 0)
			child_process();
		close_pipes(num_pipes, pipes);
		wait_all(num_cmd);
		free_all(num_pipes, pipes);
	}
}

void	child_process_bonus(int	i, int argc, char **argv, char **envp, 
		int **pipes)
{
	int		infile;
	int		outfile;
	char	*path;

	i = 0;
	if (i == 0)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile < 0)
			error_exit();
		dup2(infile, STDIN_FILENO);
		dup2(pipes[0][1], STDOUT_FILENO);
		close_pipes(num_pipes, pipes);
	}
	else if (i > count_cmd(argc, argv) - 1)
	{
		outfile = open(argv[argc - 1], O_WRONLY| O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
			error_exit();
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
	}
	else
	{
		
	}
	close(infile);
	close(outfile);
}
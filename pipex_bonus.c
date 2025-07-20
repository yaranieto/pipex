/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:58:24 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/19 19:22:22 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main_bonus(int argc, char **argv, char **envp)
{
	int		num_cmd;
	int 	numb_pipes;
	int		**pipes;

	if (argc < 5)
		error_exit();
	num_cmd = count_cmd(argc);
	numb_pipes = num_pipes(argc);
	pipes = create_pipes(numb_pipes);
	check_envp(envp);
	execute_all_bonus(argc, argv, envp, pipes);
	close_pipes(numb_pipes, pipes);
	wait_all(num_cmd);
	free_all(numb_pipes, pipes);
	return (0);
}

void	close_pipes(int	numb_pipes, int	**pipes)
{
	int	i;

	i = 0;
	while (i < numb_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
void	execute_all_bonus(int argc, char **argv, char **envp, int **pipes)
{
	int		i;
	int		num_cmd;
	pid_t	pid;
	char	*path;

	i = 0;
	num_cmd = count_cmd(argc);
	path = find_path(argv[i + 2], envp);
	while (i < num_cmd)
	{
		pid = fork();
		if (pid == -1)
			error_exit();
		if (pid == 0)
			input_output_bonus(i, argc, argv, envp, pipes);
		
		i++;
	}
	free(path);
}

void	input_output_bonus(int	i, int argc, char **argv, char **envp, 
		int **pipes)
{
	char	*path;
	char	**cmd;
	int		num_pipes;

	num_pipes = count_cmd(argc) - 1;
	cmd = ft_split(argv[i + 2], ' ');
	path = find_path(cmd[0], envp);
	if (i == 0)
		handle_input_bonus(argv, pipes, num_pipes);
	else if (i == count_cmd(argc) - 1)
		handle_output_bonus(i, argc, argv, pipes, num_pipes);
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
		close_pipes(num_pipes, pipes);
	}
	if (!path)
		error_exit();
	execve(path, cmd, envp);
	free(path);
	free_split(cmd);
	error_exit();
}

void	handle_input_bonus(char **argv, int **pipes, int num_pipes)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_exit();
	dup2(infile, STDIN_FILENO);
	dup2(pipes[0][1], STDOUT_FILENO);
	close(infile);
	close_pipes(num_pipes, pipes);
}

void	handle_output_bonus(int i, int argc, char **argv, int **pipes,
		int num_pipes)
{
	int	outfile;

	outfile = open(argv[argc - 1], O_WRONLY| O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		error_exit();
	dup2(pipes[i - 1][0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close_pipes(num_pipes, pipes);
}
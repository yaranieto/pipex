/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:58:24 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/29 22:01:17 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	if (argc < 5)
		error_exit("Menos de 4 argumentos");
	px.is_heredoc = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		px.is_heredoc = 1;
	px.argc = argc;
	px.argv = argv;
	px.envp = envp;
	if (px.is_heredoc)
		px.num_cmd = count_cmd(argc - 1);
	else
		px.num_cmd = count_cmd(argc);
	px.num_pipes = num_pipes(px.argc);
	px.pipes = create_pipes(px.num_pipes);
	check_envp(px.envp);
	execute_all_bonus(&px);
	close_pipes(px.num_pipes, px.pipes);
	wait_all(px.num_cmd);
	free_all(px.num_pipes, px.pipes);
	return (0);
}

void	execute_all_bonus(t_pipex *px)
{
	int		i;
	pid_t	pid;

	i = 0;
	if (pipe(px->pipe_molon))
		error_exit("error_exit");

	while (i < px->num_cmd)
	{
		pid = fork();
		if (pid == -1)
			error_exit("error pid");
		if (pid == 0)
			input_output_bonus(i, px);
		i++;
	}
}

void	input_output_bonus(int i, t_pipex *px)
{
	char	*path;
	char	**cmd;
	int		**pipes;

	pipes = px->pipes;
	cmd = cmd_index(i, px);
	path = find_path(cmd[0], px->envp);
	if (i == 0)
		handle_input_bonus(px);
	else if (i == px->num_cmd - 1)
		handle_output_bonus(i, px);
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
		close_pipes(px->num_pipes, px->pipes);
	}
	if (!path)
		error_exit("Error path");
	execve(path, cmd, px->envp);
	free(path);
	free_split(cmd);
	error_exit("Error execve");
}

void	handle_input_bonus(t_pipex *px)
{
	int	infile;

	if (px->is_heredoc)
	{
		handle_input_heredoc(px->argv[2], px->pipe_molon);
		dup2(px->pipe_molon[0], STDIN_FILENO);
		close(px->pipe_molon[0]);
		dup2(px->pipes[0][1], STDOUT_FILENO);
		close_pipes(px->num_pipes, px->pipes);
		close(px->pipe_molon[1]);
		return ;
	}
	else
	{
		infile = open(px->argv[1], O_RDONLY);
		if (infile < 0)
			error_exit("Error no inflie");
		dup2(infile, STDIN_FILENO);
		dup2(px->pipes[0][1], STDOUT_FILENO);
		close(infile);
		close_pipes(px->num_pipes, px->pipes);
		close(px->pipe_molon[1]);
	}
}

void	handle_output_bonus(int i, t_pipex *px)
{
	int	outfile;
	int	flags;

	if (px->is_heredoc)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		outfile = open(px->argv[px->argc - 1], flags, 0644);
		dup2(px->pipe_molon[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(px->pipe_molon[0]);
		close(outfile);
		return ;
	}
	else
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		outfile = open(px->argv[px->argc - 1], flags, 0644);
		if (outfile < 0)
			error_exit("Error no outfile");
		dup2(px->pipes[i - 1][0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close_pipes(px->num_pipes, px->pipes);
		close(outfile);
	}
}
	
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:11:49 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/08/04 16:31:21 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_input_bonus(t_pipex *px)
{
	int	infile;
	int	here_pipe[2];

	if (px->is_heredoc)
		is_heredoc(px, here_pipe);
	else
	{
		infile = open(px->argv[1], O_RDONLY);
		if (infile < 0)
			return (-1);
		dup2(infile, STDIN_FILENO);
		close(infile);
		dup2(px->pipes[0][1], STDOUT_FILENO);
		close(px->pipes[0][1]);
		close_pipes(px->num_pipes, px->pipes);
	}
	return (0);
}

int	handle_output_bonus(int i, t_pipex *px)
{
	int	outfile;
	int	flags;

	if (px->is_heredoc)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	outfile = open(px->argv[px->argc - 1], flags, 0644);
	if (outfile < 0)
		return (-1);
	if (dup2(px->pipes[i - 1][0], STDIN_FILENO) == -1)
	{
		close(outfile);
		return (-1);
	}
	close(px->pipes[i - 1][0]);
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		close(outfile);
		return (-1);
	}
	close(outfile);
	close_pipes(px->num_pipes, px->pipes);
	return (0);
}

void	handle_execution_bonus(int i, t_pipex *px)
{
	char	*path;
	char	**cmd;

	path = NULL;
	cmd = NULL;
	cmd = cmd_index(i, px);
	if (!cmd)
		clean_and_exit_bonus(NULL, NULL, px, "cmd_index failed");
	path = find_path(cmd[0], px->envp);
	if (!path)
		clean_and_exit_bonus(cmd, NULL, px, "Path no found");
	if (i == 0)
	{
		if (handle_input_bonus(px) == -1)
			clean_and_exit_bonus(cmd, path, px, "Infile no found");
	}
	else if (i == px->num_cmd - 1)
	{
		if (handle_output_bonus(i, px) == -1)
			clean_and_exit_bonus(cmd, path, px, "Outfile no found");
	}
	else
		redirect_pipes_bonus(i, px);
	execve(path, cmd, px->envp);
	clean_and_exit_bonus(cmd, path, px, "Exec error");
}

void	redirect_pipes_bonus(int i, t_pipex *px)
{
	if (dup2(px->pipes[i - 1][0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Error redirecting stdin\n", 2);
		clean_and_exit_bonus(NULL, NULL, px, "Error redirecting stdin");
	}
	close(px->pipes[i - 1][0]);
	if (dup2(px->pipes[i][1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Error redirecting stdout\n", 2);
		clean_and_exit_bonus(NULL, NULL, px, "Error redirecting stdout");
	}
	close(px->pipes[i][1]);
	close_pipes(px->num_pipes, px->pipes);
}

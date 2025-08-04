/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:21:01 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/31 17:17:53 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_input(t_pipex *px, int pipefd[2], char **cmd)
{
	int		fd_in;
	char	*path;

	fd_in = open(px->argv[1], O_RDONLY);
	if (fd_in < 0)
		clean_and_exit(px, "Infile no found");
	dup2 (fd_in, STDIN_FILENO);
	dup2 (pipefd[1], STDOUT_FILENO);
	close (fd_in);
	close (pipefd[0]);
	close (pipefd[1]);
	path = find_path(cmd[0], px->envp);
	if (!path)
		clean_and_exit(px, "Path no found");
	execve(path, cmd, px->envp);
	free(path);
	clean_and_exit(px, "Exec error");
}

void	handle_output(t_pipex *px, int pipefd[2], char **cmd)
{
	int		fd_out;
	char	*path;

	fd_out = open(px->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		clean_and_exit(px, "Outfile no found");
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(pipefd[0]);
	close(pipefd[1]);
	path = find_path(cmd[0], px->envp);
	if (!path)
		clean_and_exit(px, "Path no found");
	execve(path, cmd, px->envp);
	free(path);
	clean_and_exit(px, "Exec error");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:21:01 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/21 17:47:24 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_input(char *infile, int pipefd[2], char **cmd, char **envp)
{
	int		fd_in;
	char	*path;

	fd_in = open(infile, O_RDONLY);
	if (fd_in < 0)
		error_exit ("No hay archivo de entrada");
	dup2 (fd_in, STDIN_FILENO);
	dup2 (pipefd[1], STDOUT_FILENO);
	close (fd_in);
	close (pipefd[0]);
	close (pipefd[1]);
	printf("cmd[0]: %s\n", cmd[0]);
	path = find_path(cmd[0], envp);
	if (!path)
		error_exit("No se ha encontrado path");
	execve(path, cmd, envp);
	error_exit ("Error de ejecución");
}

void	handle_output(char *outfile, int pipefd[2], char **cmd, char **envp)
{
	int		fd_out;
	char	*path;

	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		error_exit ("No se ha encontrado archivo salida");
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(pipefd[0]);
	close(pipefd[1]);
	path = find_path(cmd[0], envp);
	if (!path)
		error_exit("No se encuentra path");
	execve(path, cmd, envp);
	error_exit ("Error de ejecución");
}

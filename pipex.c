/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:08:01 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/18 13:39:38 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main (int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	char	**cmd1_arg;
	char	**cmd2_arg;

	cmd1_arg = ft_split(argv[2], ' ');
	cmd2_arg = ft_split(argv[3], ' ');
	if (argc != 5)
		error_exit();
	check_envp(envp);
	if (pipe(pipefd) == -1)
		error_exit();
	pid1 = fork ();
	if (pid1 == -1)
		error_exit();
	if (pid1 == 0)
		handle_input(argv[1], pipefd, cmd1_arg, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_exit();
	if (pid2 == 0)
		handle_output(argv[4], pipefd, cmd2_arg, envp);
	close (pipefd[0]);
	close (pipefd[1]);
	waitpid (pid1, NULL, 0);
	waitpid (pid2, NULL, 0);
	free_split(cmd1_arg);
	free_split(cmd2_arg);
	return (0);
}

void	error_exit(void)
{
	perror ("Error");
	exit (1);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	check_envp(char **envp)
{
	if (!get_path_env(envp))
	{
		perror("No hay variables de entorno");
		error_exit();
	}
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			return ;
		envp++;
	}
	perror ("No se encontró PATH");
	error_exit();
}

void	handle_input(char *infile, int pipefd[2], char **cmd, char **envp)
{
	int		fd_in;
	char	*path;

	fd_in = open(infile, O_RDONLY);
	if (fd_in < 0)
		error_exit ();
	dup2 (fd_in, STDIN_FILENO);
	dup2 (pipefd[1], STDOUT_FILENO);
	close (fd_in);
	close (pipefd[0]); 
	close (pipefd[1]);
	path = find_path(cmd[0], envp);
	if (!path)
		error_exit();
	execve(path, cmd, envp);
	error_exit ();
}

void	handle_output(char *outfile, int pipefd[2], char **cmd, char **envp)
{
	int		fd_out;
	char	*path;

	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		error_exit ();
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(pipefd[0]);
	close(pipefd[1]);
	path = find_path(cmd[0], envp);
	if (!path)
		error_exit();
	execve(path, cmd, envp);
	error_exit ();
}


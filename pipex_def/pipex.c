/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:08:01 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/25 16:30:20 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**cmd1_arg;
	char	**cmd2_arg;

	if (argc != 5)
		error_exit("Less than 4 args");
	cmd1_arg = ft_split(argv[2], ' ');
	cmd2_arg = ft_split(argv[3], ' ');
	check_envp(envp);
	check_pipe(argv, cmd1_arg, cmd2_arg, envp);
	free_split(cmd1_arg);
	free_split(cmd2_arg);
	return (0);
}

void	check_pipe(char **argv, char **cmd1_arg, char **cmd2_arg, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		error_exit("Error pid");
	pid1 = fork ();
	if (pid1 == -1)
		error_exit("Error pid");
	if (pid1 == 0)
		handle_input(argv[1], pipefd, cmd1_arg, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("Error pid");
	if (pid2 == 0)
		handle_output(argv[4], pipefd, cmd2_arg, envp);
	close (pipefd[0]);
	close (pipefd[1]);
	waitpid (pid1, NULL, 0);
	waitpid (pid2, NULL, 0);
}

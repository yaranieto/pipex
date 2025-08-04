/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:08:01 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/31 18:25:02 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	px.cmd1_arg = NULL;
	px.cmd2_arg = NULL;
	px.argv = argv;
	px.envp = envp;
	px.argc = argc;
	if (argc != 5)
		error_exit("Only 4 args");
	px.cmd1_arg = ft_split(argv[2], ' ');
	if (!px.cmd1_arg)
		clean_and_exit(&px, "Comand1 failed");
	px.cmd2_arg = ft_split(argv[3], ' ');
	if (!px.cmd2_arg)
		clean_and_exit(&px, "Comand2 failed");
	if (!envp || !*envp)
		clean_and_exit(&px, "No envp");
	if (!get_path_env(envp))
		clean_and_exit(&px, "Path not found");
	check_process(&px);
	free_split(px.cmd1_arg);
	free_split(px.cmd2_arg);
	return (0);
}

void	check_process(t_pipex *px)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	int		status1;
	int		status2;

	if (pipe(pipefd) == -1)
		clean_and_exit(px, "Error create pid");
	pid1 = fork ();
	if (pid1 == -1)
		clean_and_exit(px, "Error on fork");
	if (pid1 == 0)
		handle_input(px, pipefd, px->cmd1_arg);
	pid2 = fork();
	if (pid2 == -1)
		clean_and_exit(px, "Error pid");
	if (pid2 == 0)
		handle_output(px, pipefd, px->cmd2_arg);
	close (pipefd[1]);
	close (pipefd[0]);
	waitpid (pid1, &status1, 0);
	waitpid (pid2, &status2, 0);
}

void	clean_and_exit(t_pipex *px, const char *msg)
{
	if (px->cmd1_arg)
		free_split(px->cmd1_arg);
	if (px->cmd2_arg)
		free_split(px->cmd2_arg);
	error_exit(msg);
}

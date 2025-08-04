/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:58:24 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/08/04 15:44:03 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	px.argc = argc;
	px.argv = argv;
	px.envp = envp;
	valid_args(&px);
	px.num_pipes = num_pipes(px.argc);
	px.pipes = create_pipes(px.num_pipes);
	if (!px.pipes)
		error_exit("Failed to create pipes");
	check_envp(px.envp);
	check_process_bonus(&px);
	close_pipes(px.num_pipes, px.pipes);
	wait_all(px.num_cmd);
	if (px.pipes)
	{
		free_all(px.num_pipes, px.pipes);
		px.pipes = NULL;
	}
	return (0);
}

void	valid_args(t_pipex	*px)
{
	if (px->argc < 4)
		error_exit("Not enough arguments");
	px->is_heredoc = 0;
	if (ft_strncmp(px->argv[1], "here_doc", 8) == 0)
		px->is_heredoc = 1;
	if (px->argc < 6 && px->is_heredoc == 1)
		error_exit("Not enough arguments");
	if (px->is_heredoc)
		px->num_cmd = count_cmd(px->argc - 1);
	else
		px->num_cmd = count_cmd(px->argc);
}

void	check_process_bonus(t_pipex *px)
{
	int		i;
	pid_t	pid;

	check_cmd(px);
	i = 0;
	while (i < px->num_cmd)
	{
		pid = fork();
		if (pid == -1)
		{
			free_all(px->num_pipes, px->pipes);
			error_exit("Error pid");
		}
		if (pid == 0)
		{
			handle_execution_bonus(i, px);
		}
		i++;
	}
}

void	check_cmd(t_pipex *px)
{
	int		i;
	char	**cmd;
	char	*path;

	i = 0;
	while (i < px->num_cmd)
	{
		cmd = cmd_index(i, px);
		if (!cmd)
		{
			close_and_free(px);
			error_exit("cmd_index failed");
		}
		path = find_path(cmd[0], px->envp);
		if (!path)
		{
			free_split(cmd);
			close_and_free(px);
			error_exit("Path no found");
		}
		free_split(cmd);
		free(path);
		i++;
	}
}

char	**cmd_index(int i, t_pipex *px)
{
	if (ft_strncmp(px->argv[1], "here_doc", 8) == 0)
		return (ft_split(px->argv[i + 3], ' '));
	else
		return (ft_split(px->argv[i + 2], ' '));
}

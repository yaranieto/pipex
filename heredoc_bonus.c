/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:04:40 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/08/04 16:32:03 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_heredoc(t_pipex *px, int *here_pipe)
{
	if (pipe(here_pipe) == -1)
		return (-1);
	handle_input_heredoc(px->argv[2], here_pipe);
	if (dup2(here_pipe[0], STDIN_FILENO) == -1)
	{
		close(here_pipe[0]);
		return (-1);
	}
	close(here_pipe[0]);
	close(here_pipe[1]);
	if (dup2(px->pipes[0][1], STDOUT_FILENO) == -1)
		return (-1);
	close(px->pipes[0][1]);
	close_pipes(px->num_pipes, px->pipes);
	return (0);
}

void	handle_input_heredoc(const char *limiter, int *here_pipe)
{
	char	buffer[4096];
	int		bytes_read;
	int		i;

	while (1)
	{
		write(1, "heredoc> ", ft_strlen("heredoc> "));
		bytes_read = read(0, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
		{
			ft_putstr_fd("Error reading from stdin\n", 2);
			break ;
		}
		buffer[bytes_read] = '\0';
		i = 0;
		while (i < bytes_read && buffer[i] != '\n')
			i++;
		if (i < bytes_read && buffer[i] == '\n')
			buffer[i] = '\0';
		if (stop_heredoc(buffer, limiter, here_pipe) == 1)
			break ;
	}
	close(here_pipe[1]);
}

int	stop_heredoc(char *buffer, const char *limiter, int *here_pipe)
{
	if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0
		&& ft_strlen(buffer) == ft_strlen(limiter))
		return (1);
	if (write(here_pipe[1], buffer, ft_strlen(buffer)) == -1
		|| write(here_pipe[1], "\n", 1) == -1)
	{
		ft_putstr_fd("Error writing to pipe\n", 2);
		return (1);
	}
	return (0);
}

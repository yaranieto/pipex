/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis <luis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:00:07 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/30 13:17:43 by luis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int numb_pipes, int **pipes)
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

void	handle_input_heredoc(const char *limiter, int here_pipe[2])
{
	char	buffer[4096];
	int		bytes_read;
	int		i;

	while (1)
	{
		write(1, "heredoc> ", 9);
		fflush(stdout);
		bytes_read = read(0, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		i = 0;
		while (i < bytes_read && buffer[i] != '\n')
			i++;
		if (i < bytes_read && buffer[i] == '\n')
			buffer[i] = '\0';
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(buffer) == ft_strlen(limiter))
			break ;
		write(here_pipe[1], buffer, ft_strlen(buffer));
		write(here_pipe[1], "\n", 1);
	}
}

char	**cmd_index(int i, t_pipex *px)
{
	if (ft_strncmp(px->argv[1], "here_doc", 8) == 0)
		return (ft_split(px->argv[i + 3], ' '));
	else
		return (ft_split(px->argv[i + 2], ' '));
}

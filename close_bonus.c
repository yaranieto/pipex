/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:00:07 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/24 17:49:40 by ynieto-s         ###   ########.fr       */
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

void	handle_input_heredoc(char *limiter, int *pipefd)
{
	char	*line;

	close(pipefd[0]);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strlen(line) == ft_strlen(limiter) + 1 &&
			ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
}

char	**cmd_index(int i, t_pipex *px)
{
	if (ft_strncmp(px->argv[1], "here_doc", 8) == 0)
		return (ft_split(px->argv[i + 3], ' '));
	else
		return (ft_split(px->argv[i + 2], ' '));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:00:07 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/25 19:15:54 by ynieto-s         ###   ########.fr       */
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
	char	*line;
	size_t	len;
	ssize_t	nread;

	line = NULL;
	len = 0;
	while (1)
	{
		write(1, "heredoc> ", 9);
		fflush(stdout);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break ;
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (strcmp(line, limiter) == 0)
			break ;
		write(here_pipe[1], line, strlen(line));
		write(here_pipe[1], "\n", 1);
	}
	free(line);
}

char	**cmd_index(int i, t_pipex *px)
{
	if (ft_strncmp(px->argv[1], "here_doc", 8) == 0)
		return (ft_split(px->argv[i + 3], ' '));
	else
		return (ft_split(px->argv[i + 2], ' '));
}

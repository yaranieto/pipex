/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:00:07 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/29 21:47:47 by yara             ###   ########.fr       */
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
	
	line = NULL;
	close(pipefd[0]);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		//printf("LINE: %s\n", line);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			printf("LINE: %s\n", limiter);
			free(line);
			break ;
			exit(1);
		}
		ft_putstr_fd(line, pipefd[1]);
		ft_putstr_fd("\n", pipefd[1]);  
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:08:01 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/12 17:47:31 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main (int argc, char **argv)
{
	pid_t	pid;
	int		fd[2];
	char	**envp;
	
	if (argc == 5)
	{
		check_envp (**envp);
		if (pid == -1)
			error_exit();
		pid = fork();
		if (pid == -1)
			error_exit();
		else if (pid == 0)
		{
			
		}
		else
		wait();
	}
	else if (argc != 5)
		error_exit();
	free (pid);
	return (0);
}

void	error_exit(void)
{
	perror ("Error");
	exit (1);
}

void	free_split(char *str)
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
	if (!envp)
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

void	child_process(char *infile, int pipefd[2], char **cmd, char **envp)
{
	int	fd_in;

	fd_in = open(infile, O_RDONLY);
	if (fd_in < 0)
		error_exit ();
	dup2 (fd_in, STDIN_FILENO);
	dup2 (pipefd[1], STDOUT_FILENO);

	close (fd_in);
	close (pipefd[0]);
	close (pipefd[1]);
	execve (cmd[0], cmd, envp);
	error_exit ();
}
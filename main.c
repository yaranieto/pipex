/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:08:01 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/14 18:29:48 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main (int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	char	**split;
	
	if (argc != 5)
		error_exit();
	check_envp(envp);
	if (pipe(pipefd) == -1)
		error_exit();
	pid1 = fork ();
	if (pid1 == -1)
		error_exit();
	if (pid1 == 0)
	{
		
	}
	pid2 = fork();
	if (pid2 == -1)
		error_exit();
	if (pid2 == 0)
	{
			
	}
	close (pipefd[0]);
	close (pipefd[1]);
	waitpid (pid1, NULL, 0);
	waitpid (pid2, NULL, 0);
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

void	parent_process(char *outfile, int pipefd[2], char **cmd, char **envp)
{
	int	fd_out;

	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		error_exit ();
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(cmd[0], cmd, envp);
	error_exit ();
}

char	*find_path(char *cmd, char **envp)
{
	char	path_env;
	char	**split;
	char	*dirs_list;
	char	path;
	
	dirs_list = ft_split(path_env, ':');
	if (cmd == '/')
	{
		if (ft_strcmp(cmd, "/", 1))
			return (cmd);
		else
			return (NULL);
		path_env = get_path_env(envp);
		if (!path_env)
			return (NULL);
		while (dirs_list)
		{
			path = join_path(dirs_list, cmd);
			if (path && access(cmd, X_OK) == 0)
				return (ft_strdup(path));
		}
	}
	return (NULL);
}

char	join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin (dir, "/");
	full = ft_strjoin (tmp, cmd);
	free (tmp);
	return (full);
}

char	get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:22:30 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/08/04 17:49:15 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <aio.h>
//#include <signal.h>

typedef struct s_pipex
{
	int		num_pipes;
	int		**pipes;
	char	**argv;
	char	**envp;
	int		argc;
	int		num_cmd;
	int		is_heredoc;
	char	**cmd1_arg;
	char	**cmd2_arg;
}	t_pipex;
char	**ft_split(const char *s, char c);
void	free_split(char **str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char *s, int start, int len);
void	ft_putstr_fd(const char *s, int fd);
void	valid_args(t_pipex	*px);
void	check_envp(char **envp);
void	check_process(t_pipex *px);
void	error_exit(const char *msg);
void	handle_input(t_pipex *px, int pipefd[2], char **cmd);
void	handle_output(t_pipex *px, int pipefd[2], char **cmd);
char	*find_path(char *cmd, char **envp);
char	*join_path(char *dir, char *cmd);
char	*get_path_env(char **envp);
char	*all_path(char *cmd, char **dirs_list);
int		count_cmd(int argc);
int		num_pipes(int argc);
int		**create_pipes(int num_pipes);
void	close_pipes(int num_pipes, int	**pipes);
void	wait_all(int num_cmd);
void	free_all(int numb_pipes, int **pipes);
void	check_process_bonus(t_pipex *px);
void	check_cmd(t_pipex *px);
void	handle_execution_bonus(int i, t_pipex *px);
void	redirect_pipes_bonus(int i, t_pipex *px);
int		handle_input_bonus(t_pipex *px);
int		handle_output_bonus(int i, t_pipex *px);
void	handle_input_heredoc(const char *limiter, int here_pipe[2]);
char	**cmd_index(int i, t_pipex *px);
void	clean_and_exit(t_pipex *px, const char *msg);
void	clean_and_exit_bonus(char **cmd, char *path,
			t_pipex *px, const char *msg);
int		handle_heredoc_error(t_pipex *px);
int		is_heredoc(t_pipex *px, int *here_pipe);
int		stop_heredoc(char *buffer, const char *limiter, int here_pipe[2]);
void	close_and_free(t_pipex *px);
void	cleanup_child_resources(char **cmd, char *path, t_pipex *px);
void	cleanup_and_exit_child(char **cmd, char *path, t_pipex *px,
			const char *msg);

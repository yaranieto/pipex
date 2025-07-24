/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:22:30 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/23 17:08:36 by ynieto-s         ###   ########.fr       */
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

typedef struct s_pipex
{
	int		num_pipes;
	int		**pipes;
	char	**argv;
	char	**envp;
	int		argc;
	int		num_cmd;
	int		is_heredoc;
}	t_pipex;
char	**ft_split(const char *s, char c);
void	free_split(char **str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char *s, int start, int len);
void	check_envp(char **envp);
void	check_pipe(char **argv, char **cmd1_arg, char **cmd2_arg, char **envp);
void	error_exit(const char *msg);
void	handle_input(char *infile, int pipefd[2], char **cmd, char **envp);
void	handle_output(char *outfile, int pipefd[2], char **cmd, char **envp);
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
void	execute_all_bonus(t_pipex *px);
void	input_output_bonus(int i, t_pipex *px);
void	handle_input_bonus(t_pipex *px);
void	handle_output_bonus(int i, t_pipex *px);
void	handle_input_heredoc(char *limiter, int *pipefd);
char	**cmd_index(int i, t_pipex *px);
char	*trim_before_newline(char *input_str);
char	*extract_line(char *input_str);
char	*read_buffer(int fd, char *buffer);
char	*free_buffer(char **buffer);
char	*get_next_line(int fd);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:22:30 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/19 19:49:43 by yara             ###   ########.fr       */
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

char	**ft_split(const char *s, char c);
void	free_split(char **str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	check_envp(char **envp);
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
void	close_pipes(int	num_pipes, int	**pipes);
void	wait_all(int num_cmd);
void	free_all(int numb_pipes, int **pipes);
void	execute_all_bonus(int argc, char **argv, char **envp, int **pipes);
void	input_output_bonus(int	i, int argc, char **argv, char **envp, 
		int **pipes);
void	handle_input_bonus(char **argv, int **pipes, int num_pipes);
void	handle_output_bonus(int i, int argc, char **argv, int **pipes,
		int num_pipes);

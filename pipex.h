/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:22:30 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/18 17:52:48 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

char	**ft_split(const char *s, char c);
void	free_split(char **str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
void	check_envp(char **envp);
void	error_exit(void);
void	handle_input(char *infile, int pipefd[2], char **cmd, char **envp);
void	handle_output(char *outfile, int pipefd[2], char **cmd, char **envp);
char	*find_path(char *cmd, char **envp);
char	*join_path(char *dir, char *cmd);
char	*get_path_env(char **envp);
void	*all_path(char *cmd, char **envp, char **dirs_list, char *path);
int		count_cmd(int argc, char **argv);
int		num_pipes(int argc, char **argv);
int		**create_pipes(int num_pipes);
void	close_pipes(int	num_pipes, int	**pipes);
void	wait_all(int num_cmd);
void	free_all(int num_pipes, int **pipes);
void	input_output_bonus(int	i, int argc, char **argv, char **envp, 
		int **pipes);
void	handle_input_bonus(int argc, char **argv, char **envp, int **pipes);
void	handle_output_bonus(int i, int argc, char **argv, char **envp,
		int **pipes);

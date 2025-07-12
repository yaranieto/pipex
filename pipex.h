/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:22:30 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/12 17:11:59 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

char	**ft_split(const char *s, char c);
void	free_split(char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
void	check_envp(char **envp);
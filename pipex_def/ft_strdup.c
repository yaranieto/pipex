/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:33:11 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/15 12:33:25 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*str2;

	i = 0;
	len = 0;
	while (str[len] != '\0')
		len++;
	str2 = (char *)malloc(sizeof(char) * (len + 1));
	if (str2 == NULL)
		return (NULL);
	else
	{
		while (str[i] != '\0')
		{
			str2[i] = str[i];
			i++;
		}
	}
	str2[i] = '\0';
	return (str2);
}

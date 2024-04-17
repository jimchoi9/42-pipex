/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:49:31 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/17 16:57:48 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_path(char **envp)
{
    int i = 0;
	char **path;
	while(envp[i] != NULL)
	{
		if(ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp[i] += 5;
			// printf("%s\n", envp[i]);
			path = ft_split(envp[i], ':');
			return (path);
		}
		i++;
	}
	path = ft_split("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", ':');
	return (path);
}

// int cmd_check(t_data *path_data, char *cmd)
// {
	
// }
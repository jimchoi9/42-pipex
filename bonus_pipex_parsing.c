/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:46:16 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/22 21:00:30 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

char	**get_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp[i] += 5;
			path = ft_split(envp[i], ':');
			return (path);
		}
		i++;
	}
	path = ft_split("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", ':');
	return (path);
}

char	*path_check(t_data *path_data, char *cmd)
{
	int	i;

	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (path_data->path[i] != NULL)
	{
		path_data->cmd_path = ft_strjoin(path_data->path[i], cmd);
		if (access(path_data->cmd_path, X_OK) == 0)
			return (path_data->cmd_path);
		i++;
	}
	handle_exit("command not found", 1);
	return (0);
}

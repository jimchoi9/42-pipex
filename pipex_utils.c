/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:50:34 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/29 19:03:29 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_exit(char *str, int status)
{
	perror(str);
	exit(status);
}

void	set_stream(int fd1, int fd2, int fd3, int fd4)
{
	if (dup2(fd1, STDIN_FILENO) == -1 || dup2(fd2, STDOUT_FILENO) == -1)
	{
		perror("dup2 error");
		exit (1);
	}
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
}

int	clean_up_resources(t_data *fd, int count)
{
	int	i;
	int	status;
	int	ret;

	i = -1;
	close(fd->infile);
	close(fd->outfile);
	close(fd->fd[0]);
	close(fd->fd[1]);
	close(fd->prev);
	while (fd->path[++i] != NULL)
		free(fd->path[i]);
	free(fd->path);
	while (count-- > 0)
	{
		if (wait(&status) == fd->pid)
		{
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
		}
	}
	return (ret);
}

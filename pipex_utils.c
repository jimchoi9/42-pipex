/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:50:34 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/18 20:15:01 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_exit(char *str, int status)
{
	perror(str);
	exit(status);
}

int	file_check(int argc, char **argv, t_fd *fd)
{
	fd->infile = open(argv[1], O_RDONLY);
	if (fd->infile == -1)
	{
		perror("infile error");
		exit (1);
	}
	fd->outfile = open(argv[argc-1], O_RDWR | O_TRUNC | O_CREAT , 0644);
	if (fd->outfile == -1)
	{
		perror("outfile error");
		exit (1);
	}
	
	return (0);
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
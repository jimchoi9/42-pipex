/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:50:34 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/29 11:51:14 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

void	handle_exit(char *str, int status)
{
	perror(str);
	exit(status);
}

void	set_stream(int fd1, int fd2, int fd3, int fd4)
{
printf("set_stream");

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
printf("cleanup resources");
	i = -1;
	close(fd->infile);
	close(fd->outfile);
	close(fd->fd[0]);
	close(fd->fd[1]);
	close(fd->prev);
	while (fd->path[++i] != NULL)
		free(fd->path[i]);
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
// int	file_check(int argc, char **argv, t_data *fd)
// {
// 	fd->infile = open(argv[1], O_RDONLY);
// 	if (fd->infile == -1)
// 	{
// 		perror("infile error");
// 		exit (1);
// 	}
// 	fd->outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
// 	if (fd->outfile == -1)
// 	{
// 		perror("outfile error");
// 		exit (1);
// 	}
// 	return (0);
// }
	// while (count-- > 0)
	// {
	// 	if (wait(&status) == fd->pid)
	// 	{
	// 		if (WIFEXITED(status))
	// 			ret = WEXITSTATUS(status);
	// 	}
	// }
	// int status;
    // int ret;
    // for (int j = 0; j < child_count; j++)
    // {
    //     if (waitpid(child_pids[j], &status, 0) != -1)
    //     {
    //         if (WIFEXITED(status))
    //             ret = WEXITSTATUS(status);
    //     }
    // }
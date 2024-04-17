/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:50:34 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/17 19:08:22 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_exit(int status)
{
	
}

int check_cmd()
{
	
	return (0);
}

int	file_check(int argc, char **argv, t_fd *fd)
{

	printf("%s : %s\n", argv[1], argv[argc-1]);
	fd->infile = open(argv[1], O_RDONLY);
	fd->outfile = open(argv[argc-1], O_WRONLY | O_TRUNC);
	if (fd->infile == -1 || fd->outfile == -1)
	{
		perror("file error");
		exit (1);
	}
	return (0);
}
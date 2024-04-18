/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:59:33 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/18 11:15:47 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "./libft/libft.h"

typedef struct s_data
{
	char	**path;
	char	*cmd_path;


} t_data;

typedef struct s_pipe
{
	int	fd[2];
	int	prev;
	int infile;
	int outfile;

} t_fd;

char **get_path(char **envp);
int	file_check(int argc, char **argv, t_fd *fd);
void	set_stream(int fd1, int fd2, int fd3, int fd4);
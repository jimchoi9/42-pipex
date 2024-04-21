/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:59:33 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/21 13:35:04 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libft_src/libft.h"

typedef struct s_pipe
{
	int		fd[2];
	int		prev;
	int		infile;
	int		outfile;
	char	**path;
	char	*cmd_path;
}			t_fd;

char	**get_path(char **envp);
void	set_stream(int fd1, int fd2, int fd3, int fd4);
void	handle_exit(char *str, int status);
int		clean_up_resources(t_fd *fd, pid_t pid, int count);
char	*path_check(t_fd *path_data, char *cmd);

#endif
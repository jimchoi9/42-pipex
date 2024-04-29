/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:59:33 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/29 17:33:10 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libft_src/libft.h"

typedef struct s_data
{
	int		fd[2];
	int		prev;
	int		infile;
	int		outfile;
	char	**path;
	char	*cmd_path;
	pid_t	pid;
}			t_data;

void	first_child(char *cmd, t_data fd, char **envp, char *infile_str);
void	last_child(char *cmd, t_data fd, char **envp, char *outfile_str);
int		init_data(t_data *fd, int argc, char **envp);
char	**get_path(char **envp);
char	*path_check(t_data *path_data, char *cmd);
void	handle_exit(char *str, int status);
void	set_stream(int fd1, int fd2, int fd3, int fd4);
int		clean_up_resources(t_data *fd, int count);

#endif
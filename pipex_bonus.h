/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:59:33 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/22 12:47:43 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libft/libft.h"

typedef struct s_data
{
	int		fd[2];
	int		prev;
	int		infile;
	int		outfile;
	char	**path;
	char	*cmd_path;
}			t_data;

char	**get_path(char **envp);
void	set_stream(int fd1, int fd2, int fd3, int fd4);
void	handle_exit(char *str, int status);
int		clean_up_resources(t_data *fd, int count);
char	*path_check(t_data *path_data, char *cmd);

#endif
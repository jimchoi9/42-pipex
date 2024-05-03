/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:11:35 by jimchoi           #+#    #+#             */
/*   Updated: 2024/05/03 12:01:58 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

void	first_child(char *cmd, t_data fd, char **envp, char *infile_str)
{
	char	*path;
	char	**commands;
	int		i;

	i = -1;
	fd.infile = open(infile_str, O_RDONLY);
	if (fd.infile == -1)
		handle_exit("infile error", 1);
	set_stream(fd.infile, fd.fd[1], fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
		handle_exit("cmd error", 1);
	path = path_check(&fd, commands[0]);
	while (fd.path[++i] != NULL)
		free(fd.path[i]);
	free(fd.path);
	if (execve(path, commands, envp) == -1)
		handle_exit("execve error", 1);
}

void	other_child(char *cmd, t_data fd, char **envp)
{
	char	*path;
	char	**commands;
	int		i;

	i = -1;
	set_stream(fd.prev, fd.fd[1], fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
		handle_exit("cmd error", 1);
	path = path_check(&fd, commands[0]);
	while (fd.path[++i] != NULL)
		free(fd.path[i]);
	free(fd.path);
	if (execve(path, commands, envp) == -1)
		handle_exit("execve error", 1);
}

void	last_child(char *cmd, t_data fd, char **envp, char *outfile_str)
{
	char	*path;
	char	**commands;
	int		i;

	i = -1;
	fd.outfile = open(outfile_str, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd.outfile == -1)
		handle_exit("outfile error", 1);
	set_stream(fd.prev, fd.outfile, fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
		handle_exit("cmd error", 1);
	path = path_check(&fd, commands[0]);
	while (fd.path[++i] != NULL)
		free(fd.path[i]);
	free(fd.path);
	if (execve(path, commands, envp) == -1)
		handle_exit("execve error", 1);
}

int	init_data(t_data *fd, int argc, char **envp)
{
	if (argc < 5)
		handle_exit("arguments error", 1);
	fd->path = get_path(envp);
	fd->prev = dup(0);
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_data	fd;

	i = init_data(&fd, argc, envp);
	while (++i < argc - 3)
	{
		pipe(fd.fd);
		fd.pid = fork();
		if (fd.pid < 0)
			handle_exit("pid error", clean_up_resources(&fd, i));
		if (fd.pid == 0)
		{
			if (i == 0)
				first_child(argv[i + 2], fd, envp, argv[1]);
			else if (i == argc - 4)
				last_child(argv[i + 2], fd, envp, argv[argc - 1]);
			else
				other_child(argv[i + 2], fd, envp);
		}
		close(fd.prev);
		close(fd.fd[1]);
		fd.prev = fd.fd[0];
	}
	return (clean_up_resources(&fd, i));
}

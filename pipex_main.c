/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:32:06 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/22 12:44:27 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(char *cmd, t_data fd, char **envp, char *infile_str)
{
	char	*path;
	char	**commands;

	fd.infile = open(infile_str, O_RDONLY);
	if (fd.infile == -1)
		handle_exit("infile error", 1);
	set_stream(fd.infile, fd.fd[1], fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
		handle_exit("cmd error", 1);
	path = path_check(&fd, commands[0]);
	execve(path, commands, envp);
	handle_exit("execve error", 1);
}

void	other_child(char *cmd, t_data fd, char **envp)
{
	char	*path;
	char	**commands;

	set_stream(fd.prev, fd.fd[1], fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
		handle_exit("cmd error", 1);
	path = path_check(&fd, commands[0]);
	execve(path, commands, envp);
	handle_exit("execve error", 1);
}

void	last_child(char *cmd, t_data fd, char **envp, char *outfile_str)
{
	char	*path;
	char	**commands;

	fd.outfile = open(outfile_str, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd.outfile == -1)
		handle_exit("outfile error", 1);
	set_stream(fd.prev, fd.outfile, fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
		handle_exit("cmd error", 1);
	path = path_check(&fd, commands[0]);
	execve(path, commands, envp);
	handle_exit("execve error", 1);
}

int	init_data(t_data *fd, int argc, char **envp)
{
	if (argc != 5)
		handle_exit("arguments error", 1);
	fd->path = get_path(envp);
	fd->prev = dup(0);
	return (-1);
}
// void check_leaks(void)
// {
// 	system("leaks pipex");
// }
//     atexit(check_leaks);

int	main(int argc, char **argv, char **envp)
{
	int		i;
	pid_t	pid;
	t_data	fd;

	i = init_data(&fd, argc, envp);
	while (++i < argc - 3)
	{
		pipe(fd.fd);
		fd.pid = fork();
		if (fd.pid < 0)
		{
			handle_exit("pid error", clean_up_resources(&fd, i));
		}
		if (fd.pid == 0)
		{
			if (i == 0)
				first_child(argv[i + 2], fd, envp, argv[1]);
			else if (i == argc - 4)
				last_child(argv[i + 2], fd, envp, argv[argc - 1]);
		}
		close(fd.prev);
		close(fd.fd[1]);
		fd.prev = fd.fd[0];
	}
	return (clean_up_resources(&fd, i));
}

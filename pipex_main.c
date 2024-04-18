/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:32:06 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/18 20:57:54 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(char *cmd, t_data path_data, t_fd fd, char **envp)
{
	int		returnv;
	char	*path;
	char	**commands;

	set_stream(fd.infile, fd.fd[1], fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
		handle_exit("cmd error", 1);
	path = path_check(&path_data, commands[0]);
	returnv = execve(path, commands, envp);
	// if (returnv == -1)
		handle_exit("execve error", 1);
	// exit(returnv);
}

void	other_child(char *cmd, t_data path_data, t_fd fd, char **envp)
{
	int		returnv;
	char	*path;
	char	**commands;

	set_stream(fd.prev, fd.fd[1], fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
		handle_exit("cmd error", 1);
	path = path_check(&path_data, commands[0]);
	returnv = execve(path, commands, envp);
	// if (returnv == -1)
		handle_exit("execve error", 1);
	// exit(returnv);
}

void	last_child(char *cmd, t_data path_data, t_fd fd, char **envp)
{
	int		returnv;
	char	*path;
	char	**commands;

	set_stream(fd.prev, fd.outfile, fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
		handle_exit("cmd error", 1);
	path = path_check(&path_data, commands[0]);
	returnv = execve(path, commands, envp);
	// if (returnv == -1)
		handle_exit("execve error", 1);
}


void check_leaks(void) 
{ system("leaks pipex"); } 

int main(int argc, char **argv, char **envp)
{

	int status;
	int i = 0;
	pid_t pid;
	t_fd fd;
	t_data path_data;

    // atexit(check_leaks);
	// printf("ac = %d\n", argc);
	if (argc < 5)
		handle_exit("too few arguments", 1);
	path_data.path = get_path(envp);
	fd.prev = dup(0);
	while(i < argc - 3)
	{
		pipe(fd.fd);
		pid = fork();
		if (pid < 0)
			handle_exit("pid error", 1);
		else if(pid == 0)
		{
			if (i == 0 && argc - 3 != 1)
			{
				fd.infile = open(argv[1], O_RDONLY);
				if (fd.infile == -1)
					handle_exit("infile error", 1);
				first_child(argv[i + 2], path_data, fd, envp);
			}
			else if(i == argc - 4)
			{
				fd.outfile = open(argv[argc-1], O_RDWR | O_TRUNC | O_CREAT , 0644);
				if (fd.outfile == -1)
					handle_exit("outfile error", 1);
				last_child(argv[i + 2], path_data, fd, envp);
			}
			else 
				other_child(argv[i + 2], path_data, fd, envp);
		}
		close(fd.prev);
		close(fd.fd[1]);
		fd.prev = fd.fd[0];
		i++;
	}
	close(fd.fd[0]);
	close(fd.fd[1]);
	close(fd.infile);
	close(fd.outfile);
	close(fd.prev);

	int j = -1;
	while (path_data.path[++j] != NULL)
		free(path_data.path[j]);
	free(path_data.path);
	int ret;
	while (i-- > 0) {
		if (wait(&status) == pid)
			if(WIFEXITED(status))
				ret = WEXITSTATUS(status);
	}
	return (ret);
}

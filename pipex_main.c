/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:32:06 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/19 14:05:52 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(char *cmd, t_fd fd, char **envp, char *infile_str)
{
	int		returnv;
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
	returnv = execve(path, commands, envp);
	// if (returnv == -1)
		handle_exit("execve error", 1);
	// exit(returnv);
}

void	other_child(char *cmd, t_fd fd, char **envp)
{
	int		returnv;
	char	*path;
	char	**commands;

	set_stream(fd.prev, fd.fd[1], fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
		handle_exit("cmd error", 1);
	path = path_check(&fd, commands[0]);
	returnv = execve(path, commands, envp);
	// if (returnv == -1)
		handle_exit("execve error", 1);
	// exit(returnv);
}

void	last_child(char *cmd, t_fd fd, char **envp, char *outfile_str)
{
	int		returnv;
	char	*path;
	char	**commands;

	fd.outfile = open(outfile_str, O_RDWR | O_TRUNC | O_CREAT , 0644);
	if (fd.outfile == -1)
		handle_exit("outfile error", 1);
	set_stream(fd.prev, fd.outfile, fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
		handle_exit("cmd error", 1);
	path = path_check(&fd, commands[0]);
	returnv = execve(path, commands, envp);
	handle_exit("execve error", 1);
}


void check_leaks(void) 
{ system("leaks pipex"); } 
    // atexit(check_leaks);

int main(int argc, char **argv, char **envp)
{
	int status;
	int i = 0;
	pid_t pid;
	t_fd fd;

	if (argc < 5)
		handle_exit("too few arguments", 1);
	fd.path = get_path(envp);
	fd.prev = dup(0);
	while(i < argc - 3)
	{
		pipe(fd.fd);
		pid = fork();
		if (pid < 0)
			handle_exit("pid error", 1);
		else if(pid == 0)
		{
			if (i == 0)
				first_child(argv[i + 2], fd, envp, argv[1]);
			else if(i == argc - 4)
				last_child(argv[i + 2], fd, envp, argv[argc-1]);
			else 
				other_child(argv[i + 2], fd, envp);
		}
		close(fd.prev);
		close(fd.fd[1]);
		fd.prev = fd.fd[0];
		i++;
	}
	close(fd.fd[0]);
	close(fd.infile);
	close(fd.outfile);
	int j = -1;
	while (fd.path[++j] != NULL)
		free(fd.path[j]);
	free(fd.path);
	int ret;
	while (i-- > 0) {
		if (wait(&status) == pid)
			if(WIFEXITED(status))
				ret = WEXITSTATUS(status);
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:32:06 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/18 17:53:22 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char	*path_check(t_data *path_data, char *cmd)
{
	int i= 0;
	int j = -1;
	
	// if (!ft_strchr(cmd, '"'))
		// return (0);
		cmd = ft_strjoin("/", cmd);
	while(path_data->path[i] != NULL)
	{
		path_data->cmd_path = ft_strjoin(path_data->path[i], cmd);
		// printf("%s\n", path_data->cmd_path);
		if (access(path_data->cmd_path, X_OK) == 0)
		{
			i = -1;

			return(path_data->cmd_path);
		}
		i++;
	}
	return(0);
}

void	first_child(char *cmd, t_data path_data, t_fd fd, char **envp)
{
	int		returnv;
	char	*path;
	char	**commands;

	set_stream(fd.infile, fd.fd[1], fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
	{
		perror("cmd error");
		exit (1);
	}
	path = path_check(&path_data, commands[0]);
	if (path == NULL)
	{
		perror("first path error");
		exit (1);
	}
	returnv = execve(path, commands, envp);
	if (returnv == -1)
	{
		perror("execve error");
		exit (1);
	}
	exit(returnv);
}

void	other_child(char *cmd, t_data path_data, t_fd fd, char **envp)
{
	int		returnv;
	char	*path;
	char	**commands;

	set_stream(fd.prev, fd.fd[1], fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
	{
		perror("cmd error");
		exit (0);
	}
	path = path_check(&path_data, commands[0]);
	if (path == NULL)
	{
		perror("second path error");
		exit (0);
	}
	returnv = execve(path, commands, envp);
	exit(returnv);
}

void	last_child(char *cmd, t_data path_data, t_fd fd, char **envp)
{
	int		returnv;
	char	*path;
	char	**commands;

	set_stream(fd.prev, fd.outfile, fd.prev, fd.fd[0]);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
	{
		perror("cmd error");
		exit (0);
	}
	path = path_check(&path_data, commands[0]);
	if (path == NULL)
	{
		perror("first path error");
		exit (0);
	}
	returnv = execve(path, commands, envp);
	if (returnv == -1)
	{
		perror("execve error");
		exit (0);
	}
	exit(returnv);
}


int main(int argc, char **argv, char **envp)
{

	int status;
	int i = 0;
	pid_t pid;
	t_fd fd;
	t_data path_data;

	if (argc < 5)
	{
		perror("too few arguments");
		exit (1);
	}
	path_data.path = get_path(envp);
	fd.prev = dup(0);
	// file_check(argc, argv, &fd);
	while(i < argc - 3)
	{
		pipe(fd.fd);
		pid = fork();
		if (pid < 0)
		{
			perror("pid error");
			exit (1);
		}
		else if(pid == 0)
		{
			if (i == 0 && argc - 3 == 1)
			{
				file_check(argc, argv, &fd);
				set_stream(fd.infile, fd.outfile, fd.fd[1], fd.prev);
				close(fd.fd[0]);
				char	*path;
				char	**commands;
				commands = ft_split(argv[i + 2], ' ');
				if (commands == NULL)
				{
					perror("cmd error");
					exit (1);
				}
				path = path_check(&path_data, commands[0]);
				if (path == NULL)
				{
					perror("first path error");
					exit (1);
				}
				if (execve(path, commands, envp) == -1)
				{
					perror("execve error");
					exit (127);
				}
			}
			if (i == 0 && argc - 3 != 1)
			{
				fd.infile = open(argv[1], O_RDONLY);
				if (fd.infile == -1)
				{
					perror("infile error");
					exit (1);
				}
				first_child(argv[i + 2], path_data, fd, envp);
			}
			else if(i == argc - 4)
			{
				fd.outfile = open(argv[argc-1], O_RDWR | O_TRUNC | O_CREAT , 0644);
				// fd.outfile = open(argv[argc-1], O_RDWR | O_TRUNC);
				if (fd.outfile == -1)
				{
					perror("outfile error");
					exit (1);
				}
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
	close(fd.infile);
	close(fd.outfile);
	close(fd.prev);
	int ret;
	while (i-- > 0) {
		if (wait(&status) == pid)
			ret = WEXITSTATUS(status);
	}
	return (ret);
}

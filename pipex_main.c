/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:32:06 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/17 20:32:30 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char	*path_check(t_data *path_data, char *cmd)
{
	int i= 0;
	int j = -1;
	
	cmd = ft_strjoin("/", cmd);
	while(path_data->path[i] != NULL)
	{
		path_data->cmd_path = ft_strjoin(path_data->path[i], cmd);
			// printf("path = %s\n", path_data->cmd_path);
		if (access(path_data->cmd_path, X_OK) == 0)
		{
			// printf("path = %s\n", path_data->cmd_path);
			i = -1;
			// while (path_data->path[++j] != NULL)
			// 	free(path_data->path[j]);
			return(path_data->cmd_path);
		}
		// free(path_data->cmd_path);
		i++;
	}
	return(0);
}

void	first_child(char *cmd, t_data path_data, t_fd fd, char **envp)
{
				dup2(fd.fd[1], STDOUT_FILENO);
				dup2(fd.infile, STDIN_FILENO);
				close(fd.fd[1]);
				close(fd.prev);

				int		returnv;
				char	*path;
				char	**commands;
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
				exit(0);
}

void	other_child(char *cmd, t_data path_data, t_fd fd, char **envp)
{
	int		returnv;
	char	*path;
	char	**commands;

				dup2(fd.fd[1], STDOUT_FILENO);
				dup2(fd.prev, STDIN_FILENO);
				close(fd.fd[1]);
				close(fd.prev);
	commands = ft_split(cmd, ' ');
	if (commands == NULL)
	{
		perror("cmd error");
		exit (1);
	}
	path = path_check(&path_data, commands[0]);
	if (path == NULL)
	{
		perror("second path error");
		exit (1);
	}
	returnv = execve(path, commands, envp);
	exit(returnv);
}

void	last_child(char *cmd, t_data path_data, t_fd fd, char **envp)
{
	dup2(fd.prev, STDIN_FILENO);
	dup2(fd.outfile, STDOUT_FILENO);
	
	close(fd.fd[1]);
	close(fd.prev);
	int		returnv;
	char	*path;
	char	**commands;
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
	exit(0);
}



int main(int argc, char **argv, char **envp)
{

	int status;
	int i = 0;
	int N = 3;
	pid_t pid;
	t_fd fd;
	t_data path_data;

	path_data.path = get_path(envp);
	fd.prev = dup(0);
	file_check(argc, argv, &fd);
	printf("%d\n", argc);
	while(i < argc - 3)
	{
		pipe(fd.fd);
		pid = fork();
		if (pid < 0)
		{
			printf("error\n");
		}
		else if(pid == 0)
		{
			if (i == 0 && argc - 3 == 1)
			{
				
				dup2(fd.outfile, STDOUT_FILENO);
				dup2(fd.infile, STDIN_FILENO);
				close(fd.fd[1]);
				close(fd.prev);
				close(fd.infile);
				close(fd.outfile);
				int		returnv;
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
				returnv = execve(path, commands, envp);
				if (returnv == -1)
				{
					perror("execve error");
					exit (1);
				}
	
				exit(returnv);
				exit(0);
			}
			if (i == 0 && argc - 3 != 1)
			{
				printf("pid child : %d :%d\n", getpid(), i);
				first_child(argv[i + 2], path_data, fd, envp);

			}
			else if(i == argc - 4)
			{
				printf("pid child : %d :%d\n", getpid(), i);
				last_child(argv[i + 2], path_data, fd, envp);
			}
			else {
				printf("pid child : %d :%d\n", getpid(), i);
				other_child(argv[i + 2], path_data, fd, envp);
			}
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
	while (i-- > 0) {
		wait(&status);
	}
printf("vnffur\n");

}

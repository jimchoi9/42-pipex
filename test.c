/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:32:06 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/16 17:19:58 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int main(int argc, char **argv, char **envp)
// {
	
// }

// #include <stdio.h>

// int main( int argc, char **argv, char **envp)
// { 
//    while( *envp)
//       printf( "%s\n", *envp++);

//    return 0;e
// }
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char * const *argv, char **envp)
{

	// printf("pid before fork : %d\n", getpid());
	int status;
	int fd[2];
	int prev = dup(0);
	int i = 0;
	int N = 3;
	pid_t pid;
	char temp = 'a';
	while(i < N)
	{
		pipe(fd);
		pid = fork();
		if (pid < 0)
		{
			printf("error\n");
		}
		else if(pid == 0)
		{
			if (i == 0)
			{
				printf("pid child : %d :%d\n", getpid(), i);
				dup2(fd[1], STDOUT_FILENO);
				// dup2(infile, STDIN_FILENO);
				char *arr[] = {"ls", NULL};
				close(fd[1]);
				close(prev);
				int returnv = execve("/bin/ls", arr, envp);
				exit(returnv);
				exit(0);
			}
			else if(i == N - 1)
			{
				printf("pid child : %d :%d\n", getpid(), i);
				dup2(prev, STDIN_FILENO);
				// dup2(outfile, STDOUT_FILENO);
				
				close(fd[1]);
				close(prev);
				char *arr[] = {"awk", "NR %2==0", NULL};
				int returnv = execve("/usr/bin/awk", arr, envp);
				exit(returnv);
				exit(0);
			}
			else {
				printf("pid child : %d :%d\n", getpid(), i);
				dup2(fd[1], STDOUT_FILENO);
				dup2(prev, STDIN_FILENO);
				close(fd[1]);
				close(prev);
				
				char *arr[] = {"cat","-e", NULL};
				int returnv = execve("/bin/cat", arr, envp);
				exit(returnv);
				
			}
		}
		close(prev);
		close(fd[1]);
		prev = fd[0];
		i++;
	}
	close(fd[0]);
	while (i-- > 0) {
		wait(&status);
	}

	perror("errorasdfasd");
}

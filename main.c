/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:32:06 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/15 15:32:49 by jimchoi          ###   ########.fr       */
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
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char * const *argv, char **envp)
{

	// printf("pid before fork : %d\n", getpid());
	int status;
	int fd[2];
	int i = 0;
	pipe(fd);

	pid_t pid;
	while(i < 3)
	{
		pid = fork();
		if (pid < 0)
		{
			printf("error\n");
		}
		else if(pid == 0)
		{
			printf("pid child : %d\n", getpid());
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			char *arr[] = {"cat","test.txt", NULL};
			int returnv = execve("/bin/cat", arr, envp);
			exit(returnv);
		}
		i++;
	}
	while (i-- > 0) {
		wait(&status);
	}
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		printf("pid parent : %d\n", getpid());
		char str[15];
		read(0, str, 15);
		printf("%s\n", str);
		printf("%d ", WEXITSTATUS(status));
	// printf("value = %d\n", returnv);
}
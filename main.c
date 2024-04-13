/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:32:06 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/13 21:33:34 by jimchoi          ###   ########.fr       */
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

	printf("pid before fork : %d\n", getpid());
	int status;
	int fd[2];

	pipe(fd);

	pid_t pid = fork();


	if (pid < 0)
	{
		printf("error\n");
	}
	if(pid == 0)
	{
		dup2(1, fd[1]);
		printf("pid child : %d\n", getpid());
		char *arr[] = {"test.txt", NULL};
		int returnv = execve("/bin/cat", arr, envp);
		exit(returnv);
	}
		dup2(fd[0], 0);
		wait(&status);
		printf("pid parent : %d\n", getpid());
		printf("%d ", WEXITSTATUS(status));
	// printf("value = %d\n", returnv);
}
#include "pipex.h"

#include <stdbool.h>	// for true/false
#include <unistd.h>		// for access() dup() dup2() fork() pipe() unlink()
#include <stdio.h>		// for perror()
#include <errno.h>		// for errno
#include <stdlib.h>		// for exit()
#include <fcntl.h>		// for pid_t open() close()
#include <sys/wait.h>	// for wait() waitpid()

//#include <sys/types.h> // for pid_t


bool ft_file_exists(char *file_path)
{
	if (access(file_path, F_OK) == -1)
		return (false);
	else
		return (true);
}

bool ft_file_readable(char *file_path)
{
	if (access(file_path, R_OK) == -1)
		return (false);
	else
		return (true);
}

bool ft_file_writeable(char *file_path)
{
	if (access(file_path, W_OK) == -1)
		return (false);
	else
		return (true);
}

bool ft_file_executable(char *file_path)
{
	if (access(file_path, X_OK) == -1)
		return (false);
	else
		return (true);
}

void	error_exit(char	*message)
{
	perror(message);
	exit(errno);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*fpath;


	int i;
	i = 0;
	while (envp[i])
		i++;
		//printf("%s\n", envp[i++]);

	fpath = "input.txt";
	printf("THIS IS TEST");
	//if (!ft_file_exists(fpath))
	//	error_exit(fpath);

	//printf("%s: File exists.\n", fpath);
	// if (access(fpath, R_OK | W_OK | X_OK) == -1)
	// 	printf("%s: Not ALL rights.\n", fpath);
	// else
	// 	printf("%s: ALL rights.\n", fpath);
	// perror("");

	// if (ft_file_readable(fpath))
	// 	printf("%s: Readable.\n", fpath);
	// else
	// 	printf("%s: Not readable.\n", fpath);

	// if (ft_file_writeable(fpath))
	// 	printf("%s: Writeable.\n", fpath);
	// else
	// 	printf("%s: Not writeable.\n", fpath);

	// if (ft_file_executable(fpath))
	// 	printf("%s: Executable.\n", fpath);
	// else
	// 	printf("%s: Not executable.\n", fpath);




	// int	pipefd[2];

	// pipe(pipefd);

	// printf("reading end of pipe (pipefd[0]): %d\n", pipefd[0]);
	// printf("writing end of pipe (pipefd[1]): %d\n", pipefd[1]);

	// printf("PID: %d\n", getpid());
	// pid_t mypid = fork();
	// int process_change_info;

	// if (mypid == 0)
	// {
	// 	printf("CHILD: Hi, i am the child. My PID is: %d\n", getpid());
	// 	printf("CHILD: I can read from my parent using fd %d\n", pipefd[0]);
	// 	printf("CHILD: doing random stuff.\n");
	// 	sleep(3);
	// 	return (0);
	// }
	// else
	// {
	// 	sleep(1);
	// 	printf("PARENT: Hi, i am the parent. My PID is: %d\n", getpid());
	// 	printf("PARENT: I can write to my child using fd %d\n", pipefd[1]);
	// 	printf("PARENT: Waiting for child to finish...\n");
	// 	wait(&process_change_info);
	// 	printf("PARENT: Child has finished.\n");
	// 	printf("PARENT: Child process change info: %d\n", process_change_info);
	// 	printf("PARENT: Child process change WEXITSTATUS: %d\n", WEXITSTATUS(process_change_info));
	// 	printf("PARENT: Child process change WIFEXITED: %d\n", WIFEXITED(process_change_info));
	// }


	// int pidx[2] = {0, 1};
	// int	x = pipe(pidx);

	// unlink(fpath);



	// if (!ft_file_readable(fpath))
	// 	printf("%s: User has no read rights.\n", fpath);

	// if (!ft_file_writeable(fpath))
	// 	printf("%s: User has no write rights.\n", fpath);

	// if (!ft_file_executable(fpath))
	// 	printf("%s: User has no execute rights.\n", fpath);

	// if (access("inputt.txt", R_OK) == -1)
	// 	printf("file does not exist");
	// else
	// 	printf("file exists");

}

#include "pipex.h"

#include <stdbool.h>	// for true/false
#include <unistd.h>	// for access()
#include <stdio.h>	// for perror()
#include <errno.h>		// for errno
#include <stdlib.h>	// for exit()


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

	fpath = "input.txt";
	//if (!ft_file_exists(fpath))
	//	error_exit(fpath);

	//printf("%s: File exists.\n", fpath);
	if (access(fpath, R_OK | W_OK | X_OK) == -1)
		printf("%s: Not ALL rights.\n", fpath);
	else
		printf("%s: ALL rights.\n", fpath);
	perror("");

	if (ft_file_readable(fpath))
		printf("%s: Readable.\n", fpath);
	else
		printf("%s: Not readable.\n", fpath);

	if (ft_file_writeable(fpath))
		printf("%s: Writeable.\n", fpath);
	else
		printf("%s: Not writeable.\n", fpath);

	if (ft_file_executable(fpath))
		printf("%s: Executable.\n", fpath);
	else
		printf("%s: Not executable.\n", fpath);

	int i;
	i = 0;

	while (envp[i])
		printf(envp[i++]);


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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:26:19 by tkasbari          #+#    #+#             */
/*   Updated: 2023/11/30 21:08:41 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	ft_file_exists(char *file_path)
{
	if (access(file_path, F_OK) == -1)
		return (false);
	else
		return (true);
}

char **ft_get_bin_paths(char *envp[])
{
	int		i;
	char	**env_path;
	int		offset;

	i = 0;
	env_path = NULL;
	offset = ft_strlen("PATH=");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", offset) == 0)
		{
			env_path = ft_split(envp[i], ':');
		}
		i++;
	}
	if (env_path && env_path[0])
		ft_memmove(env_path[0],
			env_path[0] + offset, ft_strlen(env_path[0]) - offset);
	return (env_path);
}

char	*ft_get_command_path(char *command, char **bin_paths)
{
	char	*command_path;
	int		i;

	i = 0;
	command_path = NULL;
	while (bin_paths[i])
	{
		command_path = ft_strjoin(bin_paths[i], "/");
		command_path = ft_strjoin_free(command_path, command, 1);
		if (!command_path)
			px_error_exit(ERR_MALLOC);
		if (ft_file_exists(command_path))
			return (command_path);
		free(command_path);
		i++;
	}
	return (NULL);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**bin_paths;
	char	**cmd_argv;
	char	*cmd;
	char	*cmd_path;
	int		fds[2];
	pid_t	child1;
	pid_t	child2;
	int		infile_fd;


	if (argc < 5)
		px_error_exit(ERR_TOO_FEW_ARGS);
	if (argc > 5)
		px_error_exit(ERR_TOO_MANY_ARGS);
	bin_paths = ft_get_bin_paths(envp);
	if (!bin_paths)
		px_error_exit(ERR_MALLOC);

	if (pipe(fds) == -1)
		px_error_exit("Could not create pipe");

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)/////////////////////
	{
		perror(argv[1]);
		close(STDIN_FILENO);
	}
	else
	{
		if (dup2(infile_fd, STDIN_FILENO) == -1)
			px_error_exit("Could not duplicate Infile FD");
	}

	child1 = fork();
	if (child1 == -1)
		px_error_exit("Child1 died during birth :(");
	if (child1 == 0)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			px_error_exit("Child1: Could not duplicate FD for STDOUT");
		close(fds[0]);
		close(fds[1]);
		cmd_argv = ft_split(argv[2], ' ');
		if (!cmd_argv)
				px_error_exit(ERR_MALLOC);
		cmd = cmd_argv[0];
		if (!ft_strchr(cmd, '/'))
			cmd_path = ft_get_command_path(cmd, bin_paths);
		if (!cmd_path)
			cmd_path = ft_strdup(cmd);
		execv(cmd_path, cmd_argv);
	}
	//wait(NULL);
	child2 = fork();
	if (child2 == -1)
		px_error_exit("Child2 died during birth :(");
	if (child2 == 0)
	{
		if (dup2(fds[0], STDIN_FILENO) == -1)
			px_error_exit("Child2: Could not duplicate FD for STDIN");
		close(fds[0]);
		close(fds[1]);
		cmd_argv = ft_split(argv[3], ' ');
		if (!cmd_argv)
				px_error_exit(ERR_MALLOC);
		cmd = cmd_argv[0];
		if (!ft_strchr(cmd, '/'))
			cmd_path = ft_get_command_path(cmd, bin_paths);
		if (!cmd_path)
			cmd_path = ft_strdup(cmd);
		execv(cmd_path, cmd_argv);
	}
	close(fds[0]);
	close(fds[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	//wait(NULL);


	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:07:05 by tkasbari          #+#    #+#             */
/*   Updated: 2023/11/29 22:30:11 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool ft_file_exists(char *file_path)
{
	if (access(file_path, F_OK) == -1)
		return (false);
	else
		return (true);
}

char **ft_get_path(char *envp[])
{
	int		i;
	char	**env_path;
	int		offset;

	i = 0;
	env_path = NULL;
	offset = ft_strlen("PATH=");
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", offset) == 0)
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

// char	**ft_add_str_front(char *front_str, char **strings)
// {
// 	int		i;
// 	char	**new_strings;

// 	i = 0;
// 	while (strings && strings[i])
// 		i++;
// 	//ft_putnbr_fd(i, STDOUT_FILENO);
// 	new_strings = (char **)(malloc(sizeof(char *) * (i + 2)));
// 	if (!new_strings)
// 		return (NULL);
// 	new_strings[0] = front_str;
// 	i = 0;
// 	while (strings && strings[i])
// 	{
// 		new_strings[i + 1] = strings[i];
// 		i++;
// 	}
// 	new_strings[i + 1] = NULL;
// 	return (new_strings);
// }

void	ft_print_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings && strings[i])
		ft_putendl_fd(strings[i++], STDOUT_FILENO);
}
// char	**ft_get_command_args(char *cmd, char *args)
// {
// 	char	**arguments;
// 	char	**command_with_arguments;

// 	arguments = NULL;
// 	if (args)
// 		arguments = ft_split(args, ' ');
// 	command_with_arguments = ft_add_str_front(cmd, arguments);
// 	if (arguments)
// 		free(arguments);
// 	if (!command_with_arguments)
// 		px_error_exit(ERR_MALLOC);
// 	return (command_with_arguments);
// }

// void	px_init(t_pipex *px)
// {
// 	px->char2_allocs = NULL;
// 	px->char1_allocs = NULL;
// }

// void	px_destroy(t_pipex *px)
// {
// 	t_char2_allocs	*char_star_2;
// 	t_char1_allocs	*char_star_1;

// 	char_star_2 = px->char2_allocs;
// 	char_star_1 = px->char1_allocs;
// 	while (char_star_2)
// 	{
// 		ft_free_and_null((void**)char_star_2->content);
// 		char_star_2 = char_star_2->next;
// 	}
// 	while (char_star_1)
// 	{
// 		ft_free_and_null((void**)&char_star_1->content);
// 		char_star_1 = char_star_1->next;
// 	}

// }

int	main(int argc, char *argv[], char *envp[])
{
	char	**bin_paths;
	char	**cmd_argv;
	char	*cmd;
	char	*cmd_path;
	int		i;
	pid_t	process_id;
	int		fds[2];

	if (argc < 2)
		return (EXIT_FAILURE);

	bin_paths = ft_get_path(envp);
	if (!bin_paths)
		px_error_exit(ERR_MALLOC);
	//ft_print_strings(cmd_argv);


	i = 1;
	cmd_path = NULL;
	if (pipe(fds) == -1)
		px_error_exit("Error creating pipe");
	while (argv[i])
	{
		ft_putnbr_fd(i, STDOUT_FILENO);
		process_id = fork();
		if (process_id == -1)
			px_error_exit("Child died during birth :(");
		if (process_id == 0)
		{
			dup2(fds[0], STDIN_FILENO);//////////////
			dup2(fds[1], STDOUT_FILENO);
			close(fds[0]);
			close(fds[1]);
			cmd_argv = ft_split(argv[i], ' ');
			if (!cmd_argv)
				px_error_exit(ERR_MALLOC);
			cmd = cmd_argv[0];
			if (!strchr(cmd, '/'))
				cmd_path = ft_get_command_path(cmd, bin_paths);
			if (!cmd_path)
				cmd_path = ft_strdup(cmd);
			//if (errno)
			//	perror(cmd_path);
			execv(cmd_path, cmd_argv);
			// ft_free_splitted(cmd_argv);
			// ft_free_and_null((void **)&cmd_path);
		}
		wait(NULL);
		i++;
	}

	ft_free_splitted(bin_paths);
	ft_putendl_fd("????", STDOUT_FILENO);



	//params = ft_get_command_args(cmd_path, argv[2]);

	//ft_putendl_fd(cmd_path, STDOUT_FILENO);
	//execv(cmd_path, params);
	//if (errno)
	//	perror(cmd_path);


	//ft_print_strings(argv);
	//params = ft_get_command_args(cmd_path, argv[1]);
	//params = ft_add_str_front("FIRST", NULL);
	//if (!params)
	//	px_error_exit(ERR_MALLOC);




	//printf("elements in argv: %ld\n", sizeof(argv) / sizeof(*argv));

	//i = 0;
	//while (exec_path[i])
	//	ft_putendl_fd(exec_path[i++], STDOUT_FILENO);



	return (EXIT_SUCCESS);
}

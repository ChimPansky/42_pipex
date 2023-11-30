/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:07:05 by tkasbari          #+#    #+#             */
/*   Updated: 2023/11/29 15:14:24 by tkasbari         ###   ########.fr       */
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

	i = 0;
	env_path = NULL;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = ft_split(envp[i], ':');
		}
	}
	return (env_path);
}

// char	*ft_get_executable_path(char *executable, char *env_path)
// {
// 	if (ft_file_exists(executable))
// 		return (executable);


// }

int	main(int argc, char *argv[], char *envp[])
{
	char	**exec_path;
	int		i;

	exec_path = ft_get_path(envp);
	if (!exec_path)
		px_error_exit(ERR_MALLOC);
	i = 0;
	while (exec_path[i])
		ft_putendl_fd(exec_path[i++]);
//	execv(path, argv);



	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:32:31 by tkasbari          #+#    #+#             */
/*   Updated: 2023/12/02 12:40:35 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	**ft_get_bin_paths(char *envp[])
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
			break ;
		}
		i++;
	}
	if (env_path && env_path[0])
		ft_memmove(env_path[0],
			env_path[0] + offset, ft_strlen(env_path[0]) - offset);
	return (env_path);
}

char	*ft_get_command_path(t_pipex *px, char *command)
{
	char	*command_path;
	int		i;

	i = 0;
	command_path = NULL;
	while (px->bin_paths[i])
	{
		command_path = ft_strjoin(px->bin_paths[i], "/");
		if (!command_path)
			px_error_exit(px, ERR_MALLOC);
		command_path = ft_strjoin_free(command_path, command, true, false);
		if (!command_path)
			px_error_exit(px, ERR_MALLOC);
		if (ft_file_exists(command_path))
			return (command_path);
		free(command_path);
		i++;
	}
	return (NULL);
}

void	px_set_command(t_pipex *px, char *args)
{
	char	*cmd;

	if (px->cmd_argv)
		ft_free_splitted(px->cmd_argv);
	ft_free_and_null((void **)&px->cmd_path);
	px->cmd_argv = ft_split(args, ' ');
	if (!px->cmd_argv)
		px_error_exit(px, ERR_MALLOC);
	cmd = px->cmd_argv[0];
	if (!ft_strchr(cmd, '/'))
	{
		px->cmd_path = ft_get_command_path(px, cmd);
		if (!px->cmd_path)
			px_command_not_found(px, cmd);
	}
	else
	{
		px->cmd_path = ft_strdup(cmd);
	}
}

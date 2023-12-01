/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:26:19 by tkasbari          #+#    #+#             */
/*   Updated: 2023/12/01 21:48:30 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_child_labor(t_pipex *px, char *args)
{
	if (px->child_no == 1)
	{
		px_dup2(px, px->infile_fd, STDIN_FILENO);
		close(px->infile_fd);
	}
	else
		px_dup2(px, px->pipe_fds[(px->child_no - 2) * 2], STDIN_FILENO);
	if (px->child_no == px->pipe_count + 1)
		px_dup2(px, px->outfile_fd, STDOUT_FILENO);
	else
		px_dup2(px, px->pipe_fds[(px->child_no - 1) * 2 + 1], STDOUT_FILENO);
	ft_close_child_fds(px);
	px_set_command(px, args);
	ft_putstr_fd(px->cmd_path, px->logfile_fd);
	ft_putstr_fd(px->cmd_argv[1], px->logfile_fd);
	if (execv(px->cmd_path, px->cmd_argv) == -1)
		px_error_exit(px, px->cmd_path);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	px;
	int		i;

	px_set_nulls(&px);
	if (argc < 5)
		px_error_exit(&px, ERR_TOO_FEW_ARGS);
	if (argc > 5)
		px_error_exit(&px, ERR_TOO_MANY_ARGS);
	px_init(&px, argc, argv, envp);
	i = 2;
	while (i < (argc - 1))
	{
		px.child_pid = fork();
		if (px.child_pid == -1)
			px_error_exit(&px, ERR_DEAD_CHILD);
		px.child_no++;
		if (px.child_pid == 0)
			px_child_labor(&px, argv[i]);
		waitpid(px.child_pid, NULL, 0);
		ft_close_parent_fds(&px);
		ft_print_pipe_fds(&px, px.closed_pipe_fds);
		i++;
	}
	px_destroy(&px);
	return (0);
}

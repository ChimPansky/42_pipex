/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:43:43 by tkasbari          #+#    #+#             */
/*   Updated: 2023/12/02 12:51:10 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	px_putstr_fd(t_pipex *px, char *s, int fd)
{
	if (ft_putstr_fd(s, fd) == -1)
		px_error_exit(px, ERR_WRITE);
}

void	px_dup2(t_pipex *px, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		px_error_exit(px, ERR_FD_DUP);
}

void	px_set_nulls(t_pipex *px)
{
	px->pipe_count = 0;
	px->child_no = 0;
	px->child_pid = 0;
	px->pipe_fds = NULL;
	px->closed_pipe_fds = NULL;
	px->infile_fd = 0;
	px->outfile_fd = 0;
	px->bin_paths = NULL;
	px->cmd_path = NULL;
	px->cmd_argv = NULL;
}

void	px_init(t_pipex *px, int argc, char *argv[], char *envp[])
{
	px->pipe_count = (argc - 4);
	px->infile_fd = open(argv[1], O_RDONLY);
	if (px->infile_fd == -1)
		px_error(px, argv[1]);
	px->outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (px->outfile_fd == -1)
		px_error(px, argv[argc - 1]);
	if (px->infile_fd == -1 || px->outfile_fd == -1)
		px_exit(px);
	px->pipe_fds = ft_create_pipe_fds(px);
	px->closed_pipe_fds = ft_create_pipe_fds(px);
	if (!px->pipe_fds || !px->closed_pipe_fds)
		px_error_exit(px, ERR_PIPE_FDS);
	ft_create_pipes(px);
	px->bin_paths = ft_get_bin_paths(envp);
	if (!px->bin_paths)
		px_error_exit(px, ERR_MALLOC);
}

void	px_destroy(t_pipex *px)
{
	ft_free_and_null((void **)&px->pipe_fds);
	ft_free_and_null((void **)&px->closed_pipe_fds);
	ft_free_and_null((void **)&px->cmd_path);
	if (px->bin_paths)
		ft_free_splitted(px->bin_paths);
	if (px->cmd_argv)
		ft_free_splitted(px->cmd_argv);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_file_descriptors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:35:06 by tkasbari          #+#    #+#             */
/*   Updated: 2023/12/01 22:17:46 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	*ft_create_pipe_fds(t_pipex *px)
{
	int	*fds;
	int	i;

	i = 0;
	fds = (int *)(malloc(sizeof(int) * px->pipe_count * 2));
	if (!fds)
		px_error_exit(px, ERR_MALLOC);
	while (i < (px->pipe_count * 2))
		fds[i++] = 0;
	return (fds);
}

void	ft_create_pipes(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < px->pipe_count)
	{
		if (pipe((px->pipe_fds + (i * 2))) == -1)
			px_error_exit(px, ERR_CREATE_PIPES);
		i++;
	}
}

void	px_close_fd(t_pipex *px, int fd)
{
	if (px->child_pid != 0)
		ft_putstr_fd("Parent - ", px->logfile_fd);
	ft_putstr_fd("Child No ", px->logfile_fd);
	ft_putnbr_fd(px->child_no, px->logfile_fd);
	ft_putstr_fd(": ", px->logfile_fd);
	ft_putstr_fd("Closing fd No: ", px->logfile_fd);
	ft_putnbr_fd(fd, px->logfile_fd);
	ft_putstr_fd("\n", px->logfile_fd);
	if (close(fd) == -1)
		px_error_exit(px, ERR_CLOSE_FD);
}

void	ft_close_child_fds(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < px->pipe_count * 2)
	{
		if (px->closed_pipe_fds[i] == 0)
			px_close_fd(px, px->pipe_fds[i]);
		i++;
	}
}

void	ft_close_parent_fds(t_pipex *px)
{
	if (px->child_no == 1)
	{
		px_close_fd(px, px->infile_fd);
		px_close_fd(px, px->pipe_fds[((px->child_no - 1) * 2) + 1]);
		px->closed_pipe_fds[((px->child_no - 1) * 2) + 1] = 1;
	}
	else if (px->child_no == px->pipe_count + 1)
	{
		px_close_fd(px, px->pipe_fds[(px->child_no - 2) * 2]);
		px->closed_pipe_fds[(px->child_no - 2) * 2] = 1;
	}
	else
	{
		px_close_fd(px, px->pipe_fds[(px->child_no - 2) * 2]);
		px->closed_pipe_fds[(px->child_no - 2) * 2] = 1;
		px_close_fd(px, px->pipe_fds[((px->child_no - 1) * 2) + 1]);
		px->closed_pipe_fds[((px->child_no - 1) * 2) + 1] = 1;
	}
}

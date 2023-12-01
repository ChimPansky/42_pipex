/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_logging.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:36:28 by tkasbari          #+#    #+#             */
/*   Updated: 2023/12/01 22:44:34 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	px_create_logfile(t_pipex *px)
{
	px->logfile_fd = open("pipex.log", O_RDWR | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (px->logfile_fd == -1)
		px_error_exit(px, "pipex.log");
	ft_putendl_fd("\nSTARTING LOG", px->logfile_fd);
}

void	ft_print_pipe_fds(t_pipex *px, int *fds)
{
	int	i;

	i = 0;
	while (i < px->pipe_count * 2)
	{
		ft_putstr_fd("pipe_fd[", px->logfile_fd);
		ft_putnbr_fd(i, px->logfile_fd);
		ft_putstr_fd("]: ", px->logfile_fd);
		ft_putnbr_fd(fds[i++], px->logfile_fd);
		ft_putstr_fd(".\n", px->logfile_fd);
	}
}

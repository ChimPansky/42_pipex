/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_logging.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:36:28 by tkasbari          #+#    #+#             */
/*   Updated: 2023/12/02 10:11:37 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	px_putstr_log(t_pipex *px, char *s)
{
	if (ft_putstr_fd(s, px->logfile_fd) == -1)
		px_error_exit(px, ERR_WRITE);
}

void	px_putendl_log(t_pipex *px, char *s)
{
	if (ft_putendl_fd(s, px->logfile_fd) == -1)
		px_error_exit(px, ERR_WRITE);
}

void	px_create_logfile(t_pipex *px)
{
	px->logfile_fd = open("pipex.log", O_RDWR | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (px->logfile_fd == -1)
		px_error_exit(px, "pipex.log");
	px_putendl_log(px, "\nSTARTING LOG");
}

void	ft_print_pipe_fds(t_pipex *px, int *fds)
{
	int	i;
	(void)fds;
	i = 0;
	while (i < px->pipe_count * 2)
	{
		px_putstr_log(px, "pipe_fd[");
		//ft_putnbr_fd(i, px->logfile_fd);
		px_putstr_log(px, "]: ");
		//ft_putnbr_fd(fds[i++], px->logfile_fd);
		px_putstr_log(px, ".\n");
		i++;
	}
}

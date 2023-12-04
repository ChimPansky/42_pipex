/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_error_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:04:32 by tkasbari          #+#    #+#             */
/*   Updated: 2023/12/02 13:16:39 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_command_not_found(t_pipex *px, char *cmd)
{
	px_putstr_fd(px, "command not found: ", STDERR_FILENO);
	px_putstr_fd(px, cmd, STDERR_FILENO);
	px_putstr_fd(px, "\n", STDERR_FILENO);
}

void	px_error(t_pipex *px, char *err_msg)
{
	if (errno)
	{
		px_putstr_fd(px, strerror(errno), STDERR_FILENO);
		px_putstr_fd(px, ": ", STDERR_FILENO);
	}
	if (err_msg)
		px_putstr_fd(px, err_msg, STDERR_FILENO);
	px_putstr_fd(px, "\n", STDERR_FILENO);
}

void	px_exit(t_pipex *px)
{
	px_destroy(px);
	if (errno)
		exit(errno);
	else
		exit(EXIT_FAILURE);
}

void	px_error_exit(t_pipex *px, char *err_msg)
{
	px_error(px, err_msg);
	px_exit(px);
}

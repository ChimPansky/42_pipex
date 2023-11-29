/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:04:32 by tkasbari          #+#    #+#             */
/*   Updated: 2023/11/29 21:37:43 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_error_exit(char *err_msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (errno)
		perror(err_msg);
	else
		ft_putendl_fd(err_msg, STDERR_FILENO);
	//px_destroy(px);
	if (errno)
		exit(errno);
	else
		exit(EXIT_FAILURE);
}

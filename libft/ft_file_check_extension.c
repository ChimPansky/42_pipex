/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_check_extension.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:07:02 by tkasbari          #+#    #+#             */
/*   Updated: 2023/11/15 21:07:13 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_file_check_extension(char *file_path, char *ext)
{
	char *file_extension;
	int	comparison;

	file_extension = ft_file_get_extension(file_path);
	if (!file_extension)
		return (1);
	comparison =ft_strncmp(file_extension, ext,
		ft_max(ft_strlen(file_extension), ft_strlen(ext)));
	free(file_extension);
	return (comparison);
}

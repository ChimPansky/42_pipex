/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:09:22 by tkasbari          #+#    #+#             */
/*   Updated: 2023/11/06 11:24:03 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	chose_output(int fd, int *prted, const char **fmt, va_list args);

int	ft_printf(const char *format, ...)
{
	int		printed;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	printed = ft_vdprintf(STDOUT_FILENO, format, args);
	va_end(args);
	return (printed);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int		printed;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	printed = ft_vdprintf(fd, format, args);
	va_end(args);
	return (printed);
}

int	ft_vdprintf(int fd, const char *format, va_list args)
{
	int	printed;

	printed = 0;
	while (*format)
		chose_output(fd, &printed, &format, args);
	return (printed);
}

static void	chose_output(int fd, int *prted, const char **fmt,	va_list args)
{
	t_format	conf;
	const int	already_printed = *prted;

	if (**fmt == '%')
	{
		(*fmt)++;
		if (!(**fmt))
		{
			if (*prted)
				*prted += write(fd, "%", 1);
			else
				*prted = -1;
			return ;
		}
		*prted += output_percent(fd, fmt);
		if (*prted == already_printed)
		{
			if (set_config(fmt, &conf))
				*prted += output_conversion(fd, conf, args);
			else
				*prted += output_percent(fd, fmt);
		}
	}
	else
		*prted += output_regular(fd, fmt);
}

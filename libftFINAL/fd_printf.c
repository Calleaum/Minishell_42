/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:45:02 by lgrisel           #+#    #+#             */
/*   Updated: 2024/11/01 15:45:02 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"

static int	ft_variadics(int fd, char specifier, va_list args)
{
	if (specifier == 'c')
		return (fd_print_char(fd, va_arg(args, int)));
	else if (specifier == 's')
		return (fd_print_str(fd, va_arg(args, char *)));
	else if (specifier == 'p')
		return (fd_print_pointer(fd, va_arg(args, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (fd_print_int(fd, va_arg(args, int)));
	else if (specifier == 'u')
		return (fd_print_unsigned(fd, va_arg(args, unsigned int)));
	else if (specifier == 'x')
		return (fd_print_hex(fd, va_arg(args, unsigned int), 0));
	else if (specifier == 'X')
		return (fd_print_hex(fd, va_arg(args, unsigned int), 1));
	else if (specifier == '%')
		return (write(fd, "%", 1));
	return (0);
}

int	fd_printf(int fd, const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			count += ft_variadics(fd, *format, args);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}

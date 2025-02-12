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

#include "libft.h"

static int	ft_variadics(char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (specifier == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (specifier == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_print_int(va_arg(args, int)));
	else if (specifier == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (specifier == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), 0));
	else if (specifier == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), 1));
	else if (specifier == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
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
			count += ft_variadics(*format, args);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}
/*
int	main(void)
{
	ft_printf("fauxprintf_c :%d\n", ft_printf("test :%c ", 'a'));
	printf("vraiprintf_c :%d\n", printf("test :%c ", 'a'));

	ft_printf("fauxprintf_s :%d\n", ft_printf("test :%s ", "coucou"));
	printf("vraiprintf_s :%d\n", printf("test :%s ", "coucou"));

	char	*ptr = "NULL";
	ft_printf("fauxprintf_p :%d\n", ft_printf("test :%p ", ptr));
	printf("vraiprintf_p :%d\n", printf("test :%p ", ptr));

	ft_printf("fauxprintf_i :%d\n", ft_printf("test :%i ", 32));
	printf("vraiprintf_i :%d\n", printf("test :%i ", 32));
	ft_printf("fauxprintf_d :%d\n", ft_printf("test :%d ", 32));
	printf("vraiprintf_d :%d\n", printf("test :%d ", 32));

	ft_printf("fauxprintf_u :%d\n", ft_printf("test :%u ", 32));
	printf("vraiprintf_u :%d\n", printf("test :%u ", 32));

	ft_printf("fauxprintf_x :%d\n", ft_printf("test :%x ", 32));
	printf("vraiprintf_x :%d\n", printf("test :%x ", 32));
	ft_printf("fauxprintf_X :%d\n", ft_printf("test :%X ", 32));
	printf("vraiprintf_X :%d\n", printf("test :%X ", 32));

	ft_printf("fauxprintf_ :%d\n", ft_printf("test :%% "));
	printf("vraiprintf_ :%d\n", printf("test :%% "));

	ft_printf("fauxprintf :%d\n", ft_printf("%c %s %p", 'a', "coucou", ptr));
	printf("vraiprintf :%d\n", printf("%c %s %p", 'a', "coucou", ptr));
	ft_printf("fauxprintf :%d\n", ft_printf("%i %d %x %X %% ", 32, 32, 32, 32));
	printf("vraiprintf :%d\n", printf("%i %d %x %X %% ", 32, 32, 32, 32));
	return (0);
}*/
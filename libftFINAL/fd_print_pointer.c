/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:44:51 by lgrisel           #+#    #+#             */
/*   Updated: 2024/11/01 15:44:51 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fd_hex_pointer(int fd, uintptr_t ptr)
{
	char	*hex;
	int		count;

	hex = "0123456789abcdef";
	count = 0;
	if (ptr >= 16)
		count += fd_hex_pointer(fd, ptr / 16);
	count += write(fd, &hex[ptr % 16], 1);
	return (count);
}

int	fd_print_pointer(int fd, void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		count += write(1, "(nil)", 5);
	else
	{
		count += write(1, "0x", 2);
		count += fd_hex_pointer(fd, (uintptr_t)ptr);
	}
	return (count);
}

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

static int	ft_hex_pointer(uintptr_t ptr)
{
	char	*hex;
	int		count;

	hex = "0123456789abcdef";
	count = 0;
	if (ptr >= 16)
		count += ft_hex_pointer(ptr / 16);
	count += write(1, &hex[ptr % 16], 1);
	return (count);
}

int	ft_print_pointer(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		count += write(1, "(nil)", 5);
	else
	{
		count += write(1, "0x", 2);
		count += ft_hex_pointer((uintptr_t)ptr);
	}
	return (count);
}

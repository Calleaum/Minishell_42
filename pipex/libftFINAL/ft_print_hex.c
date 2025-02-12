/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:44:48 by lgrisel           #+#    #+#             */
/*   Updated: 2024/11/01 15:44:48 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned int num, int uppercase)
{
	char	*hex;
	char	buffer[9];
	int		i;
	int		count;

	i = 8;
	count = 0;
	if (uppercase)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	buffer[i--] = '\0';
	if (num == 0)
		buffer[i--] = '0';
	else
	{
		while (num > 0)
		{
			buffer[i--] = hex[num % 16];
			num /= 16;
		}
	}
	count = write(1, &buffer[i + 1], 8 - i - 1);
	return (count);
}

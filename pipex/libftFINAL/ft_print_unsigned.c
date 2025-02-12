/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:44:58 by lgrisel           #+#    #+#             */
/*   Updated: 2024/11/01 15:44:58 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_unsigned(unsigned int n)
{
	char	*str;
	int		len;

	str = ft_uitoa(n);
	if (!str)
		return (0);
	len = ft_print_str(str);
	free(str);
	return (len);
}

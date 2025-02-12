/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:36:33 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/25 17:21:42 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
	{
		length++;
	}
	return (length);
}
/*
#include <stdio.h>
int	main(void)
{
	const char	*str = "salut";
	printf("%zu\n", ft_strlen(str));
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:58:28 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/25 17:12:35 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = 0;
}
/*
#include <stdio.h>
int	main(void)
{
	char	str[20] = "Hello, World!";

	printf("Avant ft_bzero : %s\n", str);
	ft_bzero(str + 7, 6);
	printf("Après ft_bzero : %s\n", str);
	printf("Valeurs après ft_bzero : %d %d %d %d %d %d\n",
		str[7], str[8], str[9], str[10], str[11], str[12]);
	return (0);
}*/

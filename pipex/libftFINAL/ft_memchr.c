/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:17:32 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/25 17:13:23 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ch;

	ptr = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*ptr == ch)
			return (ptr);
		ptr++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{	
	char str[] = "hello";
	char *result = (char *)ft_memchr(str, 'e', 5);
	if (result != NULL)
		printf("Found: %c\n", *result);
	else
		printf("Not Found\n");
	return (0);
}*/

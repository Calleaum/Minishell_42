/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:23:57 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/25 17:13:31 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char	str[20] = "salut";
	char	str2[20] = "coucou";
	printf("%s %s\n", str, str2);
	ft_memcpy(str2, str, 6);
	printf("%s %s\n", str, str2);
	return (0);
}*/

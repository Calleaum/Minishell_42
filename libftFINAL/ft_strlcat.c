/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:50:25 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/25 17:15:56 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	dst_len;
	unsigned int	src_len;
	unsigned int	i;

	dst_len = 0;
	src_len = 0;
	i = 0;
	while (dst[dst_len] != '\0' && dst_len < size)
		dst_len++;
	while (src[src_len] != '\0')
		src_len++;
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] != '\0' && dst_len + i < size - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str = "salut";
	char	dest[20] = "coucou";
	printf("%i\n", ft_strlcat(dest, str, 20));
	printf("%s\n", dest);
	return (0);
}*/

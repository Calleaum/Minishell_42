/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:05:20 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/25 17:16:37 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (0);
}
/*
#include <stdio.h>
int main(void)
{
	const char *str = "Hello, World!W";
	char c = 'W';
	char *result = ft_strrchr(str, c);
	printf("%ld\n",result - str);
	return 0;
}*/

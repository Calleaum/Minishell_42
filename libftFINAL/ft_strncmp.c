/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:12:23 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/25 17:16:34 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 1 && *s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
/*
#include <stdio.h>
int	main(void)
{
    char	str1[] = "coucou";
    char	str2[] = "coucou";
    int		result = ft_strncmp(str1, str2, 6);  

    printf("%d\n", result);
    return 0;
}*/

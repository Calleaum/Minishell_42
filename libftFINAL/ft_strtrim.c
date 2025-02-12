/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:12:16 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/19 14:12:16 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	result = malloc(sizeof(char) * (end - start + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, &s1[start], end - start);
	result[end - start] = '\0';
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	char *s1 = "  coucou, salut  ";
	char *result = ft_strtrim(s1, " ");
	printf("%s", result);
	free(result);
	return(0);
}*/
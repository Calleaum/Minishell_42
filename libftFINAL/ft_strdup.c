/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:12:33 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/25 17:14:09 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
#include <stdio.h>
int	main(void)
{
	const char *original = "coucou";
	char *duplicate;
	
	duplicate = ft_strdup(original);
	if (duplicate == NULL)
		return (1);
	printf("%s\n", duplicate);
	free(duplicate);
	return (0);
}*/

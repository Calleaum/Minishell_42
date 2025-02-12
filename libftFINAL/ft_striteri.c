/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:12:11 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/19 14:12:11 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
static void	ft_f(unsigned int i, char *c)
{
	*c = 'a' + i;
}*/

void	ft_striteri(char *s, void (f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s && f)
	{
		while (s[i])
		{
			f(i, &s[i]);
			i++;
		}
	}
}
/*
#include <stdio.h>
int	main(void)
{
	char str[] = "coucou";
	ft_striteri(str, ft_f);
	printf("%s\n", str);
	return (0);
}*/
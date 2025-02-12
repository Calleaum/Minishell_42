/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:14:47 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/25 17:17:12 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c = (c - 32);
		return (c);
	}
	return (c);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%i\n", ft_toupper('a'));
	return(0);
}*/

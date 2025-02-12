/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:23:24 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/25 17:17:10 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c = (c + 32);
		return (c);
	}
	return (c);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%i\n", ft_tolower('z'));
	return(0);
}*/

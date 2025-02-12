/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:31:34 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/25 17:13:41 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned int	total_s;
	void			*ptr;

	total_s = nmemb * size;
	if (nmemb != 0 && total_s / nmemb != size)
		return (NULL);
	ptr = malloc (total_s);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_s);
	return (ptr);
}
/*
#include <stdio.h>
int	main(void)
{
	int	*arr = (int *)ft_calloc(5, sizeof(int));
	for (int i = 0; i < 5; i++)
	{
		printf("%d ", arr[i]);
	}
	free (arr);
	return (0);
}*/

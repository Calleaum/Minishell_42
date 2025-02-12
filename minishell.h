/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:45:27 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/12 14:26:30 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include "libftFINAL/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_mini
{
	char	*str;
}	t_mini;

char	*get_next_line(int fd);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:50:17 by lgrisel           #+#    #+#             */
/*   Updated: 2025/01/27 14:46:25 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init(t_pipe *pip, int i, int ac)
{
	pip->end = ac - 2;
	if (i == 1)
		pip->start = 3;
	else
		pip->start = 2;
}

void	usage(void)
{
	ft_putstr_fd("\e[31mError: Bad argument \e[0m", 2);
	ft_putendl_fd("\e[32mEx:\t./pipex <file1> <cmd1> <cmd2> <...> <file2>", 1);
	ft_printf("\t\t\t./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...>", 1);
	ft_putendl_fd(" <file>\e[0m", 1);
	exit(0);
}

void	error(void)
{
	perror("\e[31mError\e[0m");
	exit (1);
}

void	init_fd(int *fd)
{
	fd[0] = -1;
	fd[1] = -1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:09:03 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/04 12:17:52 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libftFINAL/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipe
{
	char	**argv;
	char	**envp;
	int		end;
	int		start;
}	t_pipe;

void	usage(void);
void	error(void);
int		open_file(char *argv, int i);
int		get_next_line(char **line);
void	exec(char *cmd, char **envp);
char	*get_path(char **envp);
void	child(char *argv, char **envp, int input_fd, int output_fd);
void	init(t_pipe *pip, int i, int ac);
void	init_fd(int *fd);

#endif
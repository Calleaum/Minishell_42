/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:06:46 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/09 18:13:36 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_fork_error(t_node **commands, int i, int cmd_count,
				int pipe_fds[2][2])
{
	perror("minishell: fork");
	if (i < cmd_count - 1)
	{
		close(pipe_fds[i % 2][0]);
		close(pipe_fds[i % 2][1]);
	}
	while (i < cmd_count)
	{
		if (commands[i])
			free_list(commands[i]);
		i++;
	}
	free(commands);
	return (1);
}

void	setup_child_pipes(int i, int cmd_count, int pipe_fds[2][2])
{
	if (i > 0)
	{
		if (dup2(pipe_fds[(i - 1) % 2][0], STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(1);
		}
		close(pipe_fds[(i - 1) % 2][0]);
		close(pipe_fds[(i - 1) % 2][1]);
	}
	if (i < cmd_count - 1)
	{
		if (dup2(pipe_fds[i % 2][1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(1);
		}
		close(pipe_fds[i % 2][0]);
		close(pipe_fds[i % 2][1]);
	}
}

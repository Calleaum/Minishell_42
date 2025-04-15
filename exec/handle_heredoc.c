/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:51:35 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/15 16:59:33 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	setup_pipe_and_signals(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	set_sig_executing();
	return (0);
}

static int	process_line(char *line, char *delimiter, int pipe_fd, t_mini *mini)
{
	char	*expanded_line;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	else
	{
		expanded_line = expand_variables(line,
				mini->last_exit_status, mini->env, 1);
		free(line);
		line = expanded_line;
	}
	ft_putstr_fd(line, pipe_fd);
	ft_putstr_fd("\n", pipe_fd);
	free(line);
	return (0);
}

static int	read_lines(char *delimiter, int pipe_fd, t_mini *mini)
{
	char	*line;
	int		result;

	while (1)
	{
		line = readline("> ");
		if (g_signal == 130)
			break ;
		if (!line)
		{
			fd_printf(2,
				"minishell: warning: here-document delimited by end-of-file\n");
			break ;
		}
		result = process_line(line, delimiter, pipe_fd, mini);
		if (result == 1)
			break ;
	}
	return (0);
}

int	process_heredocs(t_heredoc *heredocs, t_mini *mini)
{
	t_heredoc	*current;

	current = heredocs;
	while (current)
	{
		if (setup_pipe_and_signals(current->pipe_fd) == -1)
			return (-1);
		read_lines(current->delimiter, current->pipe_fd[1], mini);
		close(current->pipe_fd[1]);
		current = current->next;
	}
	return (0);
}

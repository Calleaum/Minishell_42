/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:51:35 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/09 17:45:13 by lgrisel          ###   ########.fr       */
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
	if (ft_strchr(delimiter, '\'') == NULL)
	{
		expanded_line = expand_variables(line,
				mini->last_exit_status, mini->env);
		free(line);
		line = expanded_line;
	}
	ft_putstr_fd(line, pipe_fd);
	ft_putstr_fd("\n", pipe_fd);
	free(line);
	return (0);
}

static int	read_lines(char *delimiter, int pipe_fds[2], t_mini *mini)
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
		result = process_line(line, delimiter, pipe_fds[1], mini);
		if (result == 1)
			break ;
	}
	close(pipe_fds[1]);
	return (0);
}

int	handle_heredoc(char *delimiter, t_mini *mini)
{
	int	pipe_fds[2];

	if (setup_pipe_and_signals(pipe_fds) == -1)
		return (-1);
	read_lines(delimiter, pipe_fds, mini);
	if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
	{
		close(pipe_fds[0]);
		perror("minishell: dup2");
		return (-1);
	}
	close(pipe_fds[0]);
	return (0);
}

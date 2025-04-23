/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_rl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:38:48 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/23 17:01:21 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_line(char *line, char *delimiter, int pipe_fd, t_mini *mini)
{
	char	*expanded_line;

	if (!line)
	{
		fd_printf(2,
			"minishell: warning: here-document delimited by end-of-file\n");
		return (1);
	}
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	expanded_line = expand_variables(line, mini->last_exit_status,
			mini->env, 1);
	free(line);
	if (!expanded_line)
		return (1);
	ft_putstr_fd(expanded_line, pipe_fd);
	ft_putstr_fd("\n", pipe_fd);
	free(expanded_line);
	return (0);
}

static char	*heredoc_child_process(int fd, char *delimiter, t_mini *mini,
						t_node **cmd)
{
	char	*line;

	signal(SIGINT, sig_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (g_signal == 130)
		{
			close(fd);
			mini->last_exit_status = 130;
			free_env(mini->env);
			free_all(cmd, NULL, mini->cmd_count);
			exit(130);
		}
		if (process_line(line, delimiter, fd, mini))
			break ;
	}
	close(fd);
	return (NULL);
}

static char	*handle_heredoc_file_creation(char *count_str,
				int *fd)
{
	char	*filename;

	filename = ft_strjoin("/tmp/.heredoc_", count_str);
	free(count_str);
	if (!filename)
		return (NULL);
	*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		free(filename);
		return (NULL);
	}
	return (filename);
}

static char	*handle_parent_process(pid_t pid, char *filename, t_mini *mini)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		g_signal = 130;
		mini->last_exit_status = 130;
		unlink(filename);
		free(filename);
		return (NULL);
	}
	return (filename);
}

char	*create_heredoc_file(char *delimiter, t_mini *mini, t_node **cmd,
				char **filenames)
{
	int			fd;
	char		*filename;
	static int	heredoc_count = 0;
	char		*count_str;
	pid_t		pid;

	count_str = ft_itoa(heredoc_count++);
	if (!count_str)
		return (NULL);
	filename = handle_heredoc_file_creation(count_str, &fd);
	if (!filename)
		return (NULL);
	pid = fork();
	if (pid == 0)
	{
		while (--mini->l >= 0)
			free(filenames[mini->l]);
		free(filenames);
		free(filename);
		heredoc_child_process(fd, delimiter, mini, cmd);
		free_env(mini->env);
		free_all(cmd, NULL, mini->cmd_count);
		exit(0);
	}
	return (close(fd), handle_parent_process(pid, filename, mini));
}

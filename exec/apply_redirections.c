/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:00:15 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/15 17:58:52 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		perror("minishell: dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_output_trunc(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("minishell: dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_output_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("minishell: dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

static int	process_redirection(t_node *current, t_heredoc **heredocs)
{
	int			i;
	int			result;
	static int	heredoc_index = 0;
	t_heredoc	*current_heredoc;

	i = -1;
	result = 0;
	if (current->type == IF && current->next)
		result = handle_input_file(current->next->data);
	else if (current->type == OT && current->next)
		result = handle_output_trunc(current->next->data);
	else if (current->type == OA && current->next)
		result = handle_output_append(current->next->data);
	else if (current->type == HD && current->next)
	{
		current_heredoc = *heredocs;
		while (++i < heredoc_index && current_heredoc)
			current_heredoc = current_heredoc->next;
		if (current_heredoc)
		{
			result = handle_processed_heredoc(current_heredoc->pipe_fd[0]);
			heredoc_index++;
		}
	}
	return (result);
}

int	apply_redirections(t_node *tokens, t_mini *mini)
{
	static int			first_call = 1;
	static t_heredoc	*heredocs = NULL;
	t_node				*current;
	int					result;

	if (first_call--)
	{
		heredocs = collect_heredocs(tokens);
		if (heredocs)
			if (process_heredocs(heredocs, mini) == -1)
				return (free_heredocs(heredocs), heredocs = NULL, -1);
	}
	current = tokens;
	while (current)
	{
		if ((current->type == IF || current->type == OT
				|| current->type == OA || current->type == HD) && current->next)
		{
			result = process_redirection(current, &heredocs);
			if (result == -1)
				return (free_heredocs(heredocs), 1);
		}
		current = current->next;
	}
	return (free_heredocs(heredocs), 0);
}

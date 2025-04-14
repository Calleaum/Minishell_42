/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:00:15 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/14 17:28:58 by calleaum         ###   ########.fr       */
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

static int	process_redirection(t_node *current, t_mini *mini)
{
	int	result;

	result = 0;
	if (current->type == INPUT_FILE && current->next)
		result = handle_input_file(current->next->data);
	else if (current->type == OUTPUT_TRUNC && current->next)
		result = handle_output_trunc(current->next->data);
	else if (current->type == OUTPUT_APPEND && current->next)
		result = handle_output_append(current->next->data);
	else if (current->type == HEREDOC && current->next)
		result = handle_heredoc(current->next->data, mini);
	return (result);
}

int	apply_redirections(t_node *tokens, t_mini *mini)
{
	t_node	*current;
	int		result;

	current = tokens;
	while (current)
	{
		if ((current->type == INPUT_FILE || current->type == OUTPUT_TRUNC
				|| current->type == OUTPUT_APPEND || current->type == HEREDOC)
			&& current->next)
		{
			result = process_redirection(current, mini);
			if (result == -1)
				return (1);
			current = current->next;
		}
		current = current->next;
	}
	return (0);
}

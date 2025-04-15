/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:50:54 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/15 18:02:01 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_heredoc	*create_heredoc_node(char *delimiter)
{
	t_heredoc	*new_node;

	new_node = malloc(sizeof(t_heredoc));
	if (!new_node)
		return (NULL);
	new_node->delimiter = ft_strdup(delimiter);
	if (!new_node->delimiter)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

static void	add_heredoc(t_heredoc **heredocs, t_heredoc *new_node)
{
	t_heredoc	*current;

	if (!*heredocs)
	{
		*heredocs = new_node;
		return ;
	}
	current = *heredocs;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

t_heredoc	*collect_heredocs(t_node *tokens)
{
	t_node		*current;
	t_heredoc	*heredocs;
	t_heredoc	*new_node;

	heredocs = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == HD && current->next)
		{
			new_node = create_heredoc_node(current->next->data);
			if (!new_node)
			{
				free_heredocs(heredocs);
				return (NULL);
			}
			add_heredoc(&heredocs, new_node);
			current = current->next;
		}
		current = current->next;
	}
	return (heredocs);
}

void	free_heredocs(t_heredoc *heredocs)
{
	t_heredoc	*current;
	t_heredoc	*next;

	current = heredocs;
	while (current)
	{
		next = current->next;
		if (current->delimiter)
			free(current->delimiter);
		free(current);
		current = next;
	}
}

int	handle_processed_heredoc(int pipe_fd)
{
	if (dup2(pipe_fd, STDIN_FILENO) == -1)
	{
		close(pipe_fd);
		perror("minishell: dup2");
		return (-1);
	}
	close(pipe_fd);
	return (0);
}

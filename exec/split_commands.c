/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:37:38 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/24 14:01:47 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_node	*copy_token_list(t_node *start, t_node *end)
{
	t_node	*head;
	t_node	*current;
	t_node	*new_token;

	head = NULL;
	current = start;
	while (current && current != end)
	{
		new_token = create_token(current->data, current->type);
		if (!new_token)
		{
			free_list(head);
			return (NULL);
		}
		add_token(&head, new_token);
		current = current->next;
	}
	return (head);
}

static int	count_commands(t_node *tokens)
{
	t_node	*current;
	int		count;

	count = 1;
	current = tokens;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

static int	add_segment(t_node **commands, int index,
					t_node *start, t_node *end)
{
	commands[index] = copy_token_list(start, end);
	if (!commands[index])
		return (0);
	return (1);
}

static int	extract_segments(t_node **commands, t_node *tokens)
{
	t_node	*current;
	t_node	*start;
	int		i;

	i = 0;
	current = tokens;
	start = current;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (!add_segment(commands, i, start, current))
				return (i - 1);
			i++;
			start = current->next;
		}
		current = current->next;
	}
	if (start && !add_segment(commands, i, start, NULL))
		return (i);
	return (-1);
}

t_node	**split_commands(t_node *tokens, t_mini *mini)
{
	t_node	**commands;
	int		count;
	int		error_index;

	count = count_commands(tokens);
	commands = allocate_commands(count);
	if (!commands)
		return (NULL);
	error_index = extract_segments(commands, tokens);
	if (error_index != -1)
		return (clean_commands(commands, error_index));
	mini->cmd_count = count;
	return (commands);
}

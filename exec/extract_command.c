/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:43:11 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/08 10:48:33 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_command_args(t_node *tokens)
{
	t_node	*current;
	int		count;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == CMD || current->type == ARG)
		{
			count++;
			current = current->next;
		}
		else
			break ;
	}
	return (count);
}

static int	fill_args_array(t_node *tokens, char **args, int count)
{
	t_node	*current;
	int		i;

	i = 0;
	current = tokens;
	while (current && i < count)
	{
		if (current->type == CMD || current->type == ARG)
		{
			args[i] = ft_strdup(current->data);
			if (!args[i])
				return (-1);
			i++;
		}
		current = current->next;
	}
	args[i] = NULL;
	return (0);
}

char	**extract_command_args(t_node *tokens)
{
	int		count;
	char	**args;
	int		result;
	int		i;

	count = count_command_args(tokens);
	args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	result = fill_args_array(tokens, args, count);
	if (result == -1)
	{
		i = 0;
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
		return (NULL);
	}
	return (args);
}

t_node	*extract_command_token(t_node *tokens)
{
	t_node	*current;
	t_node	*head;
	t_node	*new_token;

	head = NULL;
	current = tokens;
	while (current && (current->type == CMD || current->type == ARG))
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:42:12 by lgrisel           #+#    #+#             */
/*   Updated: 2025/03/11 18:44:54 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_startfinal(t_node **head, char **current_token, int *i, int oui)
{
	if (!oui)
	{
		if (*current_token)
		{
			add_token(head,
				create_token(*current_token, get_token_type(*current_token)));
			free(*current_token);
			*current_token = NULL;
		}
		(*i)++;
	}
	else
	{
		if (*current_token)
		{
			add_token(head,
				create_token(*current_token, get_token_type(*current_token)));
			free(*current_token);
		}
	}
}

void	process_special_char(t_node **head, char **current_token,
								char *input, int *i)
{
	if (*current_token)
	{
		add_token(head,
			create_token(*current_token, get_token_type(*current_token)));
		free(*current_token);
		*current_token = NULL;
	}
	handle_special_char(head, input, i);
}

int	handle_quotes(t_node **head, char **current_token, char *input, int *i)
{
	char	*quoted_part;
	char	*temp;

	quoted_part = process_quoted_section(input, i, input[*i]);
	if (!quoted_part)
	{
		if (*current_token)
			free(*current_token);
		return (free_list(*head), 0);
	}
	if (*current_token)
	{
		temp = ft_strjoin(*current_token, quoted_part);
		free(*current_token);
		free(quoted_part);
		if (!temp)
			return (free_list(*head), 0);
		*current_token = temp;
	}
	else
		*current_token = quoted_part;
	return (1);
}

int	handle_regular_char(t_node **head, char **current_token, char c, int *i)
{
	int	result;

	if (!*current_token)
		result = init_new_token(current_token, c);
	else
		result = append_to_token(current_token, c);
	if (!result)
	{
		if (*current_token)
			free(*current_token);
		return (free_list(*head), 0);
	}
	(*i)++;
	return (1);
}

t_node	*tokenize_input(char *input, t_mini *t)
{
	t_node	*head;

	init_tokenization(&head, t);
	while (input[t->i])
	{
		if (ft_isspace(input[t->i]))
		{
			handle_startfinal(&head, &t->current_token, &t->i, 0);
			continue ;
		}
		if (input[t->i] == '<' || input[t->i] == '>' || input[t->i] == '|')
		{
			process_special_char(&head, &t->current_token, input, &t->i);
			continue ;
		}
		if (input[t->i] == '"' || input[t->i] == '\'')
		{
			if (!handle_quotes(&head, &t->current_token, input, &t->i))
				return (NULL);
			continue ;
		}
		if (!handle_regular_char(&head, &t->current_token, input[t->i], &t->i))
			return (NULL);
	}
	return (handle_startfinal(&head, &t->current_token, &t->i, 1), head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:42:12 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/09 16:06:58 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_startfinal(t_node **head, t_mini *t, int *i, int oui)
{
	if (!oui)
	{
		if (t->current_token)
		{
			add_token(head, create_token(t->current_token,
					get_token_type(t->current_token, t)));
			free(t->current_token);
			t->current_token = NULL;
		}
		(*i)++;
	}
	else if (t->current_token)
	{
		add_token(head, create_token(t->current_token,
				get_token_type(t->current_token, t)));
		free(t->current_token);
	}
}

static int	is_special(char *quoted_part)
{
	if (!ft_strncmp(quoted_part, "<", INT_MAX))
		return (1);
	if (!ft_strncmp(quoted_part, "<<", INT_MAX))
		return (1);
	if (!ft_strncmp(quoted_part, ">", INT_MAX))
		return (1);
	if (!ft_strncmp(quoted_part, ">>", INT_MAX))
		return (1);
	if (!ft_strncmp(quoted_part, "|", INT_MAX))
		return (1);
	return (0);
}

static int	handle_quotes(t_node **head, t_mini *t, char *input, int *i)
{
	char	*quoted_part;
	char	*temp;

	quoted_part = process_quoted_section(input, i, input[*i]);
	if (is_special(quoted_part))
		t->special = 1;
	if (!quoted_part)
	{
		if (t->current_token)
			free(t->current_token);
		return (free_list(*head), 0);
	}
	if (t->current_token)
	{
		temp = ft_strjoin(t->current_token, quoted_part);
		free(t->current_token);
		free(quoted_part);
		if (!temp)
			return (free_list(*head), 0);
		t->current_token = temp;
	}
	else
		t->current_token = quoted_part;
	return (1);
}

static int	handle_regular_char(t_node **head, char **current_token
	, char c, int *i)
{
	int	mallocerror;

	if (!*current_token)
		mallocerror = init_new_token(current_token, c);
	else
		mallocerror = append_to_token(current_token, c);
	if (!mallocerror)
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
			handle_startfinal(&head, t, &t->i, 0);
			continue ;
		}
		if (input[t->i] == '"' || input[t->i] == '\'')
		{
			if (!handle_quotes(&head, t, input, &t->i))
				return (NULL);
			continue ;
		}
		if (!handle_regular_char(&head, &t->current_token, input[t->i], &t->i))
			return (NULL);
	}
	return (handle_startfinal(&head, t, &t->i, 1), head);
}

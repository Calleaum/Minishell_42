/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:57:21 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/08 18:31:10 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_tokenization(t_node **head, t_mini *t)
{
	*head = NULL;
	t->i = 0;
	t->current_token = NULL;
	t->quoted_part = NULL;
	t->special = 0;
}

int	init_new_token(char **current_token, char c)
{
	*current_token = (char *)malloc(2);
	if (!*current_token)
		return (0);
	(*current_token)[0] = c;
	(*current_token)[1] = '\0';
	return (1);
}

t_node	*create_token(char *value, int type)
{
	t_node	*new_token;

	new_token = (t_node *)malloc(sizeof(t_node));
	if (!new_token)
		return (NULL);
	new_token->data = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_node **head, t_node *new_token)
{
	t_node	*temp;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
}

void	free_list(t_node *head)
{
	t_node	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->data);
		free(temp);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:37:16 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/25 08:42:45 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *env)
{
	t_env_node	*sorted_list;
	t_env_node	*current;
	char		*equals;

	sorted_list = build_sorted_env_list(env);
	if (!sorted_list)
		return ;
	current = sorted_list;
	while (current)
	{
		equals = ft_strchr(current->var, '=');
		if (equals)
		{
			*equals = '\0';
			printf("declare -x %s=\"%s\"\n", current->var, equals + 1);
			*equals = '=';
		}
		else
			printf("declare -x %s\n", current->var);
		current = current->next;
	}
	free_env_list(sorted_list);
}

static t_env_node	*create_env_node(char *var)
{
	t_env_node	*node;

	node = malloc(sizeof(t_env_node));
	if (!node)
		return (NULL);
	node->var = ft_strdup(var);
	if (!node->var)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

static void	insert_sorted(t_env_node **head, t_env_node *new_node)
{
	t_env_node	*current;

	if (*head == NULL || ft_strcmp((*head)->var, new_node->var) > 0)
	{
		new_node->next = *head;
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL
		&& ft_strcmp(current->next->var, new_node->var) < 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
}

t_env_node	*build_sorted_env_list(t_env *env)
{
	t_env_node	*head;
	t_env_node	*new_node;
	t_env_node	*temp;
	int			i;

	head = NULL;
	i = 0;
	while (i < env->count)
	{
		new_node = create_env_node(env->env_vars[i]);
		if (!new_node)
		{
			while (head)
			{
				temp = head;
				head = head->next;
				free(temp->var);
				free(temp);
			}
			return (NULL);
		}
		insert_sorted(&head, new_node);
		i++;
	}
	return (head);
}

int	ft_export(t_mini *mini, t_node *list)
{
	t_node	*current;
	int		success;
	int		arg_result;

	if (list->next == NULL)
	{
		print_env(mini->env);
		return (1);
	}
	current = list->next;
	success = 1;
	while (current != NULL)
	{
		arg_result = handle_export_arg(mini, current->data);
		if (arg_result == 0)
			success = 0;
		current = current->next;
	}
	return (success);
}

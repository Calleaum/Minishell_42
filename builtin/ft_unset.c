/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:44:20 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/24 14:00:19 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	remove_env_var(t_env *env, const char *var_name)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < (size_t)env->count)
	{
		if (check_env_match(env->env_vars[i], var_name))
		{
			free(env->env_vars[i]);
			j = i;
			while (++j < (size_t)env->count)
				env->env_vars[j - 1] = env->env_vars[j];
			env->env_vars[--env->count] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	remove_env_var_from_tokens(t_node **head, const char *var_name)
{
	t_node	*current;
	t_node	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (check_token_match(current->data, var_name))
		{
			prev->next = current->next;
			free(current->data);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

static int	handle_unset_arg(t_env *env, char *arg)
{
	remove_env_var(env, arg);
	remove_env_var_from_tokens(&env->tokens, arg);
	return (1);
}

int	ft_unset(t_mini *mini, t_node *list)
{
	t_node	*current;
	int		exit_status;

	exit_status = 0;
	if (!list->next)
	{
		mini->last_exit_status = 0;
		return (1);
	}
	current = list->next;
	while (current != NULL)
	{
		if (!handle_unset_arg(mini->env, current->data))
			exit_status = 1;
		current = current->next;
	}
	mini->last_exit_status = exit_status;
	return (1);
}

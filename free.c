/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:00:23 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/19 12:26:19 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_vars(char **env_vars)
{
	int	i;

	i = 0;
	while (env_vars[i] != NULL)
	{
		free(env_vars[i]);
		i++;
	}
}

void	free_env(t_env *env)
{
	if (!env)
		return ;
	free_env_vars(env->env_vars);
	free(env->env_vars);
	free(env);
}

void	free_env_list(t_env_node *head)
{
	t_env_node	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->var);
		free(temp);
	}
}

void	free_listenv(t_mini *mini, t_node *list)
{
	free_list(list);
	free_env(mini->env);
}

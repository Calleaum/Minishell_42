/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:00:23 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/27 17:34:16 by lgrisel          ###   ########.fr       */
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

void	free_all(t_mini *mini, t_node **commands, char **args, int cmd_count)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	free_env(mini->env);
	if (commands)
	{
		while (++i < cmd_count && commands[i])
			free_list(commands[i]);
		free(commands);
	}
	if (args)
	{
		while (args[++j])
			free(args[j]);
		free(args);
	}
}

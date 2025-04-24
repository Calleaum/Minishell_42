/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:43:49 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/24 14:09:40 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_mini *mini, t_node *args)
{
	int	i;

	if (!mini || !mini->env || !mini->env->env_vars)
	{
		fd_printf(2, "env: environment not found\n");
		mini->last_exit_status = 1;
		return (1);
	}
	if (args && args->next)
	{
		fd_printf(2, "env: '%s': No such file or directory\n",
			args->next->data);
		mini->last_exit_status = 127;
		return (127);
	}
	i = 0;
	while (i < mini->env->count)
	{
		if (mini->env->env_vars[i] && strchr(mini->env->env_vars[i], '='))
			printf("%s\n", mini->env->env_vars[i]);
		i++;
	}
	mini->last_exit_status = 0;
	return (0);
}

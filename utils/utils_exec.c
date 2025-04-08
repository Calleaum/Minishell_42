/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:48:41 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/08 16:51:25 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	**allocate_commands(int count)
{
	t_node	**commands;

	commands = (t_node **)malloc(sizeof(t_node *) * count);
	return (commands);
}

t_node	**clean_commands(t_node **commands, int index)
{
	while (index >= 0)
	{
		free_list(commands[index]);
		index--;
	}
	free(commands);
	return (NULL);
}

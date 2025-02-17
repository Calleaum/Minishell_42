/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:05:21 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/17 17:04:26 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_directory(t_mini *mini)
{
	char	*path;

	path = expand_variables(mini->str + 3, mini->last_exit_status);
	if (path)
	{
		if (chdir(path) == -1)
			perror("cd");
		free(path);
	}
	else
	{
		printf("Error: failed to expand path\n");
	}
}

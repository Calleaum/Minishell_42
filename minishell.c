/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:36 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/12 14:43:58 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_mini *mini, int	i)
{
	if (mini->str)
		free(mini->str);
	exit (i);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	
	if (ac != 1)
		return (ft_putstr("No arguments needed\n"), 0);
	while (1)
	{
		ft_putstr("pouet$ ");
		mini.str = get_next_line(0);
		if (!(ft_strncmp(mini.str, "exit", 4)) && ft_strlen(mini.str) == 5)
			clean_exit(&mini, 0);
		free(mini.str);
	}
	if (ac)
		return (0);
	if (av)
		return (0);
	if (env)
		return (0);
}

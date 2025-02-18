/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:36 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/18 12:13:14 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean(t_mini *mini)
{
	int	j;

	if (mini->str)
		free(mini->str);
	if (mini->args)
	{
		j = 0;
		while (mini->args[j])
		{
			free(mini->args[j]);
			j++;
		}
		free(mini->args);
	}
}

void	is_command(t_mini *mini)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	if (!mini->str || mini->str[0] == '\0')
		return ;
	while (mini->str[i] == ' ' || (mini->str[i] >= 9 && mini->str[i] <= 13))
		i++;
	k = i;
	while (mini->str[i] && !(mini->str[i] == ' '
			|| (mini->str[i] >= 9 && mini->str[i] <= 13)))
	{
		i++;
		j++;
	}
	if (j > 0)
	{
		mini->tmpstr = ft_substr(mini->str, k, j);
		printf("%s: command not found\n", mini->tmpstr);
		free(mini->tmpstr);
	}
}

void	handle_command(t_mini *mini)
{
	char	*expanded_str;

	if (only_space(mini))
		return ;
	else if (!(ft_strncmp(mini->str, "exit", 4)) && strlenus(mini->str) == 4)
		ft_exit(mini);
	else if (ft_strncmp(mini->str, "echo", 4) == 0
		&& (mini->str[4] == ' ' || mini->str[4] == '\0'))
	{
		expanded_str = expand_variables(mini->str, mini->last_exit_status);
		ft_echo(expanded_str);
		free(expanded_str);
	}
	else if (ft_strncmp(mini->str, "cd", 2) == 0)
		change_directory(mini);
	else
		is_command(mini);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	mini.last_exit_status = 0;
	if (ac != 1 && av && env)
		return (printf("No arguments needed\n"), 1);
	while (1)
	{
		mini.str = readline("minishell$ ");
		if (!mini.str)
			break ;
		add_history(mini.str);
		mini.args = ft_split_all(mini.str);
		handle_command(&mini);
		clean(&mini);
	}
}

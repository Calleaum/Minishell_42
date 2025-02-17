/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:36 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/17 08:48:53 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_mini *mini, int i)
{
	if (mini->str)
		free(mini->str);
	if (mini->args)
		free(mini->args);
	exit(i);
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
	int		i;
	char	*expanded_str;

	if (only_space(mini))
		return ;
	else if (!(ft_strncmp(mini->str, "exit", 4)) && strlenus(mini->str) == 4)
	{
		if (count_words_skipall(mini->str) > 2)
			clean_exit(mini, 1);
		else if (isdigit_str(mini->str + 5))
		{
			i = ft_atoi(mini->str + 5);
			clean_exit(mini, i);
		}
		else if (strlenws(mini->str) != ft_strlen(mini->str) - 1)
			clean_exit(mini, 2);
		clean_exit(mini, 0);
	}
	else if (ft_strncmp(mini->str, "echo", 4) == 0
		&& (mini->str[4] == ' ' || mini->str[4] == '\0'))
	{
		expanded_str = expand_variables(mini->str, mini->last_exit_status);
		ft_echo(expanded_str);
		free(expanded_str);
	}
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
		mini.args = ft_split_all(mini.str);
		handle_command(&mini);
		free(mini.str);
	}
}

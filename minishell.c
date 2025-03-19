/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:36 by lgrisel           #+#    #+#             */
/*   Updated: 2025/03/19 12:29:10 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command(t_mini *mini, t_node *list)
{
	if (!(ft_strncmp(list->data, "exit", INT_MAX)))
		ft_exit(mini, list);
	else if (!ft_strncmp(list->data, "echo", INT_MAX))
		ft_echo(list->next);
	else if (!ft_strncmp(list->data, "cd", INT_MAX))
		ft_cd(mini, list);
	else if (!ft_strncmp(list->data, "pwd", INT_MAX))
		ft_pwd(mini);
	else if (!ft_strncmp(list->data, "env", INT_MAX))
		ft_env(mini, list);
	else if (!ft_strncmp(list->data, "export", INT_MAX))
		ft_export(mini->env, list);
	else if (!ft_strncmp(list->data, "unset", INT_MAX))
		ft_unset(mini->env, list, mini);
	else
		if (list == NULL)
			printf("Token: , $ in single quote: 0\n");
		else
			printf("%s: command not found\n", list->data);
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	t_node *list = NULL;

	setup_signals();
	mini.last_exit_status = 0;
	init_mini(&mini, env);
	if (ac != 1 && av && env)
		return (printf("No arguments needed\n"), 1);
	while (1)
	{
		mini.str = readline("minishell$ ");
		if (!mini.str)
		{
			free(mini.str);
			free_env(mini.env);
			break ;
		}
		if (empty_line(mini.str))
			continue ;
		add_history(mini.str);
		if (count_words(mini.str, &mini) == (size_t)-1)
		{
			free(mini.str);
			continue ;
		}
		char *oui = expand_variables(mini.str, mini.last_exit_status, mini.env);
		if (*oui == '\0')
		{
			free(oui);
			free(mini.str);
			continue;
		}
		list = tokenize_input(oui, &mini);
		free(oui);
		handle_command(&mini, list);
		free_list(list);
		free(mini.str);
	}
}

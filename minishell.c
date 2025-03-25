/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:36 by lgrisel           #+#    #+#             */
/*   Updated: 2025/03/25 15:34:01 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_command(t_mini *mini, t_node *list)
// {
// 	if (!ft_strncmp(list->data, "exit", INT_MAX))
// 		ft_exit(mini, list);
// 	else if (!ft_strncmp(list->data, "echo", INT_MAX))
// 		ft_echo(mini, list->next);
// 	else if (!ft_strncmp(list->data, "cd", INT_MAX))
// 		ft_cd(mini, list);
// 	else if (!ft_strncmp(list->data, "pwd", INT_MAX))
// 		ft_pwd(mini);
// 	else if (!ft_strncmp(list->data, "env", INT_MAX))
// 		ft_env(mini, list);
// 	else if (!ft_strncmp(list->data, "export", INT_MAX))
// 		ft_export(mini, list);
// 	else if (!ft_strncmp(list->data, "unset", INT_MAX))
// 		ft_unset(mini, list);
// 	else
// 		ft_printf("%s: command not found\n", list->data);
// }

static int	empty_line(char *line)
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

static int	is_unclosedquote(char *str)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !dq)
			sq = !sq;
		else if (str[i] == '"' && !sq)
			dq = !dq;
		i++;
	}
	if (sq || dq)
		return (ft_putendl_fd("Error: Unclosed quote detected", 2), -1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	t_node	*list;

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
			write(2, "exit\n", 5);
			break ;
		}
		if (empty_line(mini.str))
			continue ;
		add_history(mini.str);
		if (is_unclosedquote(mini.str))
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
		free(mini.str);
		list = tokenize_input(oui, &mini);
		free(oui);
		execute_pipeline(&mini, list);
		// handle_command(&mini, list);
		// free_list(list);
	}
}

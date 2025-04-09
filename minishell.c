/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:36 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/09 16:06:30 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal = 0;

static int	execute_command(t_mini *mini)
{
	t_node	*list;

	add_history(mini->str);
	if (is_unclosedquote(mini->str))
		return (free(mini->str), 0);
	mini->exp = expand_variables(mini->str, mini->last_exit_status, mini->env);
	free(mini->str);
	if (*mini->exp == '\0')
		return (free(mini->exp), 0);
	g_signal = 0;
	list = tokenize_input(mini->exp, mini);
	free(mini->exp);
	if (*list->data == '\0')
	{
		write(2, "minishell: : command not found\n", 31);
		return (free_list(list), 0);
	}
	if (check_pipe_syntax(list) || check_redir_syntax(list))
		return (free_list(list), 0);
	if (has_heredoc(list))
		set_sig_interactive(1);
	execute_pipeline(mini, list);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	init_mini(&mini, env);
	if (ac != 1 && av && env)
		return (printf("No arguments needed\n"), 1);
	while (1)
	{
		set_sig_interactive(0);
		mini.str = readline("minishell$ ");
		if (!mini.str)
			return (write(2, "exit\n", 5), free_env(mini.env), 0);
		if (empty_line(mini.str))
			continue ;
		execute_command(&mini);
	}
}

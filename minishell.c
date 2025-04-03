/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:36 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/03 16:15:57 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal = 0;

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	t_node	*list;

	init_mini(&mini, env);
	mini.last_exit_status = 0;
	if (ac != 1 && av && env)
		return (printf("No arguments needed\n"), 1);
	while (1)
	{
		set_sig_interactive();
		if (!(mini.str = readline("minishell$ ")))
			return (write(2, "exit\n", 5), free_env(mini.env), 0);
		if (empty_line(mini.str))
			continue ;
		if (is_unclosedquote(mini.str))
		{
			free(mini.str);
			continue ;
		}
		add_history(mini.str);
		mini.strvar = expand_variables(mini.str, mini.last_exit_status, mini.env);
		free(mini.str);
		if (*mini.strvar == '\0')
		{
			free(mini.strvar);
			continue ;
		}
		g_signal = 0;
		list = tokenize_input(mini.strvar, &mini);
		free(mini.strvar);
		if (*list->data == '\0')
		{
			write(2, "minishell: : command not found\n", 31);
			free_list(list);
			continue ;
		}
		if (check_pipe_syntax(list) || check_redir_syntax(list))
		{
			free_list(list);
			continue ;
		}
		execute_pipeline(&mini, list);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:36 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/02 14:56:49 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal = 0;

static int	check_redir_syntax(t_node *list)
{
	t_node	*temp;

	temp = list;
	while (temp && temp->next)
	{
		if (temp->type == INPUT_FILE || temp->type == HEREDOC
			|| temp->type == OUTPUT_TRUNC || temp->type == OUTPUT_APPEND)
		{
			if (temp->next->type == INPUT_FILE || temp->next->type == HEREDOC
				|| temp->next->type == OUTPUT_TRUNC
				|| temp->next->type == OUTPUT_APPEND)
				return (fd_printf(2
						, "minishell: error near unexpected token `%s'\n"
						, temp->next->data), 1);
		}
		temp = temp->next;
	}
	if (!temp->next && (temp->type == INPUT_FILE || temp->type == HEREDOC
			|| temp->type == OUTPUT_TRUNC || temp->type == OUTPUT_APPEND))
		return (fd_printf(2
				, "minishell: error near unexpected token `newline'\n"), 1);
	return (0);
}

static int	check_pipe_syntax(t_node *list)
{
	t_node	*temp;

	temp = list;
	if (temp->type == PIPE)
		return (fd_printf(2, MSG), 1);
	while (temp && temp->next && temp->next->next)
	{
		if (temp->next->type == PIPE && (temp->type == INPUT_FILE
				|| temp->type == HEREDOC || temp->type == OUTPUT_TRUNC
				|| temp->type == OUTPUT_APPEND))
			return (fd_printf(2, MSG), 1);
		if (temp->type == PIPE && (temp->next->type == OUTPUT_TRUNC
				|| temp->next->type == HEREDOC || temp->next->type == INPUT_FILE
				|| temp->next->type == OUTPUT_APPEND))
			if (temp->next->next->type != CMD && temp->next->next->type != ARG)
				return (fd_printf(2, MSG), 1);
		temp = temp->next;
	}
	while (temp && temp->next)
		temp = temp->next;
	if (temp->type == PIPE)
		return (fd_printf(2, MSG), 1);
	return (0);
}

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

	init_mini(&mini, env);
	mini.last_exit_status = 0;
	if (ac != 1 && av && env)
		return (printf("No arguments needed\n"), 1);
	while (1)
	{
		g_signal = 0;
		set_sig_interactive();
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
		char *str = expand_variables(mini.str, mini.last_exit_status, mini.env);
		if (*str == '\0')
		{
			free(str);
			free(mini.str);
			continue ;
		}
		g_signal = 0;
		free(mini.str);
		list = tokenize_input(str, &mini);
		free(str);
		if (*list->data == '\0')
		{
			free_list(list);
			write(2, "minishell: : command not found\n", 31);
			continue ;
		}
		if (check_pipe_syntax(list))
		{
			free_list(list);
			continue ;
		}
		if (check_redir_syntax(list))
		{
			free_list(list);
			continue ;
		}
		execute_pipeline(&mini, list);
	}
}

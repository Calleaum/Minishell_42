/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:59:58 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/14 12:48:20 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	is_unclosedquote(char *str)
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

int	check_redir_syntax(t_node *list)
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
						, "minishell: syntax error near unexpected token `%s'\n"
						, temp->next->data), 1);
		}
		temp = temp->next;
	}
	if (!temp->next && (temp->type == INPUT_FILE || temp->type == HEREDOC
			|| temp->type == OUTPUT_TRUNC || temp->type == OUTPUT_APPEND))
		return (fd_printf(2, MSGREDIR), 1);
	return (0);
}

int	check_pipe_syntax(t_node *list)
{
	t_node	*temp;

	temp = list;
	if (temp->type == PIPE)
		return (fd_printf(2, MSGPIPE), 1);
	while (temp && temp->next && temp->next->next)
	{
		if (temp->next->type == PIPE && (temp->type == INPUT_FILE
				|| temp->type == HEREDOC || temp->type == OUTPUT_TRUNC
				|| temp->type == OUTPUT_APPEND))
			return (fd_printf(2, MSGPIPE), 1);
		if (temp->type == PIPE && (temp->next->type == OUTPUT_TRUNC
				|| temp->next->type == HEREDOC || temp->next->type == INPUT_FILE
				|| temp->next->type == OUTPUT_APPEND))
			if (temp->next->next->type != CMD && temp->next->next->type != ARG)
				return (fd_printf(2, MSGPIPE), 1);
		temp = temp->next;
	}
	while (temp && temp->next)
		temp = temp->next;
	if (temp->type == PIPE)
		return (fd_printf(2, MSGPIPE), 1);
	return (0);
}

int	has_heredoc(t_node *list)
{
	t_node	*temp;

	temp = list;
	if (temp)
	{
		if (!ft_strcmp(temp->data, "cat") || !ft_strcmp(temp->data, "as"))
			return (2);
	}
	while (temp && temp->next)
	{
		if (temp->type == HEREDOC)
			return (1);
		temp = temp->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:34:57 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/24 14:25:59 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_heredoc(t_node *current, t_mini *mini, t_node **cmd,
				char **filenames)
{
	t_node	*next;
	char	*filename;

	while (current && mini->l < mini->count)
	{
		if (current->type == HD && current->next)
		{
			next = current->next;
			filename = create_heredoc_file(next->data, mini, cmd, filenames);
			if (!filename)
			{
				while (--mini->l >= 0)
					free(filenames[mini->l]);
				return (free(filenames), 1);
			}
			filenames[mini->l++] = filename;
		}
		current = current->next;
	}
	return (0);
}

void	for_command(t_node *current, t_mini *mini, char **filenames)
{
	t_node	*next;

	while (current)
	{
		if (current->type == HD && current->next)
		{
			next = current->next;
			free(current->data);
			current->data = ft_strdup("<");
			current->type = IF;
			free(next->data);
			next->data = filenames[mini->l++];
		}
		current = current->next;
	}
}

int	process_heredocs_for_command(t_node *tokens, t_mini *mini, t_node **cmd)
{
	t_node	*current;
	char	**filenames;

	mini->count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == HD)
			mini->count++;
		current = current->next;
	}
	if (mini->count == 0)
		return (0);
	filenames = malloc(sizeof(char *) * mini->count);
	if (!filenames)
		return (1);
	mini->l = 0;
	current = tokens;
	if (process_heredoc(current, mini, cmd, filenames))
		return (1);
	mini->l = 0;
	current = tokens;
	for_command(current, mini, filenames);
	return (free(filenames), 0);
}

// 🖕
int	prepare_heredocs(t_node **commands, t_mini *mini)
{
	int	i;
	int	result;

	i = 0;
	while (i < mini->cmd_count)
	{
		if (!commands[i])
			continue ;
		result = process_heredocs_for_command(commands[i], mini, commands);
		if (result != 0)
			return (1);
		i++;
	}
	return (0);
}

void	cleanup_heredoc_files(t_node **commands, int cmd_count)
{
	int		i;
	t_node	*current;

	i = 0;
	while (i < cmd_count)
	{
		if (!commands[i])
			continue ;
		current = commands[i];
		while (current)
		{
			if (current->type == IF && current->next
				&& ft_strncmp(current->next->data, "/tmp/.heredoc_", 24) == 0)
				unlink(current->next->data);
			current = current->next;
		}
		i++;
	}
}

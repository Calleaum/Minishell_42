/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:34:57 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/22 18:35:32 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_line(char *line, char *delimiter, int pipe_fd, t_mini *mini)
{
	char	*expanded_line;

	if (!line)
		return (1);
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	expanded_line = expand_variables(line, mini->last_exit_status, mini->env, 1);
	free(line);
	if (!expanded_line)
		return (1);
	ft_putstr_fd(expanded_line, pipe_fd);
	ft_putstr_fd("\n", pipe_fd);
	free(expanded_line);
	return (0);
}

static char	*create_heredoc_file(char *delimiter, t_mini *mini, t_node **cmd, char	**filenames)
{
	int			fd;
	char		*filename;
	char		*line;
	static int	heredoc_count = 0;
	char		*count_str;

	count_str = ft_itoa(heredoc_count++);
	if (!count_str)
		return (NULL);
	
	filename = ft_strjoin("/tmp/.minishell_heredoc_", count_str);
	free(count_str);
	if (!filename)
		return (NULL);
	
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(filename);
		return (NULL);
	}
	pid_t pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sig_handler_heredoc);
		while (1)
		{
			line = readline("> ");
			if (g_signal == 130)
				break;
			if (!line)
			{
				fd_printf(2, "minishell: warning: here-document delimited by end-of-file\n");
				break;
			}
			if (process_line(line, delimiter, fd, mini))
				break;
		}
		close(fd);
		while (--mini->l >= 0)
			free(filenames[mini->l]);
		free(filenames);
		free(filename);
		free_env(mini->env);
		free_all(cmd, NULL, mini->cmd_count);
		exit(0);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			g_signal = 130;
			mini->last_exit_status = 130;
			return (NULL); // heredoc was canceled
		}
	}
	close(fd);
	return (filename);  // Retourne le nom du fichier au lieu du descripteur
}

/*
** Processes each heredoc in the command
** Uses a simple linear traversal to find and process each heredoc
** as they appear in the token list
*/
int	process_heredocs_for_command(t_node *tokens, t_mini *mini, t_node **cmd)
{
	t_node	*current;
	t_node	*next;
	char	*filename;
	char	**filenames;
	int		count;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == HD)
			count++;
		current = current->next;
	}
	if (count == 0)
		return (0);
	filenames = malloc(sizeof(char *) * count);
	if (!filenames)
		return (1);
	mini->l = 0;
	current = tokens;
	while (current && mini->l < count)
	{
		if (current->type == HD && current->next)
		{
			next = current->next;
			filename = create_heredoc_file(next->data, mini, cmd, filenames);
			if (!filename)
			{
				while (--mini->l >= 0)
					free(filenames[mini->l]);
				free(filenames);
				return (1);
			}
			filenames[mini->l++] = filename;
		}
		current = current->next;
	}
	mini->l = 0;
	current = tokens;
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
	free(filenames);
	return (0);
}

int	prepare_heredocs(t_node **commands, t_mini *mini)
{
	int	i;
	int	result;

	for (i = 0; i < mini->cmd_count; i++)
	{
		if (!commands[i])
			continue;
		result = process_heredocs_for_command(commands[i], mini, commands);
		if (result != 0)
			return (1);
	}
	return (0);
}

// Cette fonction est à ajouter pour nettoyer les fichiers temporaires
void	cleanup_heredoc_files(t_node **commands, int cmd_count)
{
	int		i;
	t_node	*current;

	for (i = 0; i < cmd_count; i++)
	{
		if (!commands[i])
			continue;
		current = commands[i];
		while (current)
		{
			if (current->type == IF && current->next && 
				ft_strncmp(current->next->data, "/tmp/.minishell_heredoc_", 24) == 0)
				unlink(current->next->data);
			current = current->next;
		}
	}
}

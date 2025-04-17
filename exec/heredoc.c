/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:34:57 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/17 20:01:30 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_line(char *line, char *delimiter, int pipe_fd, t_mini *mini)
{
	char	*expanded_line;
	
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	else
	{
		expanded_line = expand_variables(line,
				mini->last_exit_status, mini->env, 1);
		free(line);
		line = expanded_line;
	}
	ft_putstr_fd(line, pipe_fd);
	ft_putstr_fd("\n", pipe_fd);
	free(line);
	return (0);
}

static int	create_heredoc_file(char *delimiter, t_mini *mini)
{
	int		fd;
	char	*filename;
	char	*line;
	static int	heredoc_count = 0;
	char	*count_str;

	count_str = ft_itoa(heredoc_count++);
	if (!count_str)
		return (-1);
	filename = ft_strjoin("/tmp/.minishell_heredoc_", count_str);
	free(count_str);
	if (!filename)
		return (-1);
	
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(filename);
		return (-1);
	}
	
	// Read from stdin until delimiter is found
	while (1)
	{
		if (g_signal == 130)
			break ;
		line = readline("> ");
		if (!line)
		{
			fd_printf(2,
				"minishell: warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (process_line(line, delimiter, fd, mini))
			break;
	}
	
	close(fd);
	
	fd = open(filename, O_RDONLY);
	unlink(filename);  // Delete file when closed
	free(filename);
	return (fd);
}

/* 
** Create a string representation of the file descriptor path
** Format: "/proc/self/fd/XX" where XX is the file descriptor number
*/
static char	*create_fd_path(int fd)
{
	char	*prefix;
	char	*fd_str;
	char	*result;
	
	prefix = ft_strdup("/proc/self/fd/");
	if (!prefix)
		return (NULL);
	
	fd_str = ft_itoa(fd);
	if (!fd_str)
	{
		free(prefix);
		return (NULL);
	}
	
	result = ft_strjoin(prefix, fd_str);
	free(prefix);
	free(fd_str);
	
	return (result);
}

/*
** Processes each heredoc in the command
** Uses a simple linear traversal to find and process each heredoc
** as they appear in the token list
*/
int	process_heredocs_for_command(t_node *tokens, t_mini *mini)
{
	t_node	*current;
	t_node	*next;
	int		fd;
	int		*fd_array;
	int		count;
	int		i;
	char	*fd_path;
	
	// First count the heredocs to allocate an array for file descriptors
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
		
	fd_array = (int *)malloc(sizeof(int) * count);
	if (!fd_array)
		return (1);
	
	// Now process each heredoc in order of appearance
	i = 0;
	current = tokens;
	while (current)
	{
		if (current->type == HD && current->next)
		{
			next = current->next;
			fd = create_heredoc_file(next->data, mini);
			if (fd == -1)
			{
				// Clean up previously opened fds
				while (--i >= 0)
					close(fd_array[i]);
				free(fd_array);
				return (1);
			}
			fd_array[i++] = fd;
			
			// Convert HEREDOC to input file
			free(current->data);
			current->data = ft_strdup("<");
			current->type = IF;
			
			// Replace delimiter with fd path using our function instead of sprintf
			fd_path = create_fd_path(fd);
			if (!fd_path)
			{
				// Clean up on error
				while (i >= 0)
					close(fd_array[--i]);
				free(fd_array);
				return (1);
			}
			free(next->data);
			next->data = fd_path;
		}
		current = current->next;
	}
	
	free(fd_array);
	return (0);
}

int	prepare_heredocs(t_node **commands, int cmd_count, t_mini *mini)
{
	int	i;
	int	result;
	
	for (i = 0; i < cmd_count; i++)
	{
		if (!commands[i])
			continue;
			
		result = process_heredocs_for_command(commands[i], mini);
		if (result != 0)
			return (1);
	}
	
	return (0);
}

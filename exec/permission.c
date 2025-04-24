/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:56:37 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/24 14:18:14 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_path_errors(char *cmd)
{
	if ((cmd[0] == '/' && cmd[1] == '/')
		|| (ft_strlen(cmd) >= 3 && cmd[ft_strlen(cmd) - 1] == '/'
			&& cmd[ft_strlen(cmd) - 2] == '/'
			&& cmd[ft_strlen(cmd) - 3] == '/'))
	{
		fd_printf(2, "minishell: %s: No such file or directory\n", cmd);
		return (127);
	}
	return (0);
}

int	check_file_permissions(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		fd_printf(2, "minishell: %s: No such file or directory\n", cmd);
		return (127);
	}
	if (access(cmd, X_OK) == -1)
	{
		fd_printf(2, "minishell: %s: Permission denied\n", cmd);
		return (126);
	}
	return (0);
}

char	*get_command_path(char *cmd, t_mini *mini)
{
	char	*path;
	int		error;

	if (ft_strchr(cmd, '/'))
	{
		error = check_file_permissions(cmd);
		if (error != 0)
			return (NULL);
		path = ft_strdup(cmd);
	}
	else
	{
		path = find_command_path(cmd, mini);
		if (!path)
			print_command_not_found(cmd);
	}
	return (path);
}

int	check_is_directory(char *path, char *cmd)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir != NULL)
	{
		closedir(dir);
		fd_printf(2, "minishell: %s: Is a directory\n", cmd);
		free(path);
		return (126);
	}
	return (0);
}

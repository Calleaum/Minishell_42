/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:56:32 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/24 14:24:53 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin(t_mini *mini, t_node *tokens)
{
	if (!ft_strcmp(tokens->data, "echo"))
		ft_echo(mini, tokens->next);
	if (!ft_strcmp(tokens->data, "cd"))
		return (ft_cd(mini, tokens));
	else if (!ft_strcmp(tokens->data, "pwd"))
		return (ft_pwd(mini));
	else if (!ft_strcmp(tokens->data, "export"))
		return (ft_export(mini, tokens));
	else if (!ft_strcmp(tokens->data, "unset"))
		return (ft_unset(mini, tokens));
	else if (!ft_strcmp(tokens->data, "env"))
		return (ft_env(mini, tokens));
	else if (!ft_strcmp(tokens->data, "exit"))
		ft_exit(mini, tokens);
	return (0);
}

char	*find_command_path(char *cmd, t_mini *mini)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
	path_env = get_env_value(mini->env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin3(paths[i], "/", cmd);
		if (!full_path)
			return (free_paths(paths), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_paths(paths), full_path);
		free(full_path);
	}
	return (free_paths(paths), NULL);
}

void	print_command_not_found(const char *cmd)
{
	char		buffer[256];
	int			i;
	int			j;
	const char	*prefix;
	const char	*suffix;

	i = -1;
	prefix = "minishell: ";
	while (prefix[++i])
		buffer[i] = prefix[i];
	j = -1;
	while (cmd[++j] && i < 250)
	{
		buffer[i] = cmd[j];
		i++;
	}
	suffix = ": command not found\n";
	j = -1;
	while (suffix[++j] && i < 255)
	{
		buffer[i] = suffix[j];
		i++;
	}
	buffer[i] = '\0';
	write(2, buffer, i);
}

static int	process_child(char *path, char **args, t_mini *mini)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), free(path), 1);
	else if (pid == 0)
	{
		if (execve(path, args, mini->env->env_vars) == -1)
		{
			perror("minishell: execve");
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (1);
	}
	return (0);
}

int	execute_external_command(t_mini *mini, char **args)
{
	char	*path;
	int		error;

	if (!args || !args[0])
		return (1);
	error = handle_path_errors(args[0]);
	if (error != 0)
		return (mini->last_exit_status = error, error);
	path = get_command_path(args[0], mini);
	if (!path)
		return (mini->last_exit_status = 127, 127);
	error = check_is_directory(path, args[0]);
	if (error != 0)
		return (mini->last_exit_status = error, error);
	if (process_child(path, args, mini))
		return (mini->last_exit_status = 1, 1);
	return (0);
}

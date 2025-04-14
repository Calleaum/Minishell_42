/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:09:36 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/14 13:27:16 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	execute_single_command(t_mini *mini, t_node **cmd, int cmd_count)
{
	int		stdin_copy;
	int		stdout_copy;
	int		exit_status;
	t_node	*token;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (apply_redirections(cmd[0], mini) != 0)
		return (dup2(stdin_copy, STDIN_FILENO), dup2(stdin_copy, STDOUT_FILENO),
			close(stdin_copy), close(stdout_copy), 1);
	if (!ft_strcmp(cmd[0]->data, "exit"))
	{
		close(stdin_copy);
		close(stdout_copy);
	}
	token = extract_command_token(cmd[0]);
	free_all(cmd, NULL, cmd_count);
	exit_status = execute_builtin(mini, token);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	free_list(token);
	return (exit_status);
}

static int	execute_child_command(t_mini *mini, t_node **commands,
								int i, int cmd_count)
{
	t_node	*token;
	int		exit_status;
	char	**args;

	if (apply_redirections(commands[i], mini) != 0)
		return (1);
	if (commands[i] && commands[i]->type == CMD)
	{
		token = extract_command_token(commands[i]);
		free_all(commands, NULL, cmd_count);
		exit_status = execute_builtin(mini, token);
		return (free_list(token), free_env(mini->env), exit_status);
	}
	else if (commands[i] && commands[i]->type == ARG)
	{
		args = extract_command_args(commands[i]);
		if (!args)
			exit(1);
		exit_status = execute_external_command(mini, args);
		return (free_all(commands, args, cmd_count), free_env(mini->env),
			exit_status);
	}
	else
		return (free_all(commands, NULL, cmd_count), free_env(mini->env), 0);
}

static int	fork_and_execute(t_mini *mini, t_node **commands,
							int cmd_count, int pipe_fds[2][2])
{
	pid_t	pid;

	if (mini->j < cmd_count - 1)
	{
		if (pipe(pipe_fds[mini->j % 2]) == -1)
			return (perror("minishell: pipe"),
				free_all(commands, NULL, cmd_count), 1);
	}
	pid = fork();
	if (pid == -1)
		return (handle_fork_error(commands, mini->j, cmd_count, pipe_fds));
	else if (pid == 0)
	{
		setup_child_pipes(mini->j, cmd_count, pipe_fds);
		exit(execute_child_command(mini, commands, mini->j, cmd_count));
	}
	if (mini->j > 0)
	{
		close(pipe_fds[(mini->j - 1) % 2][0]);
		close(pipe_fds[(mini->j - 1) % 2][1]);
	}
	return (0);
}

static int	wait_for_children(int cmd_count, t_mini *mini)
{
	int	i;
	int	status;
	int	exit_status;

	exit_status = 0;
	i = -1;
	while (++i < cmd_count)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_status = 128 + WTERMSIG(status);
	}
	mini->last_exit_status = exit_status;
	return (exit_status);
}

int	execute_pipeline(t_mini *mini, t_node *tokens)
{
	int		cmd_count;
	t_node	**commands;
	int		pipe_fds[2][2];
	int		exit_status;

	commands = split_commands(tokens, &cmd_count);
	free_list(tokens);
	if (!commands)
		return (1);
	if (cmd_count == 1 && commands[0] && commands[0]->type == CMD)
	{
		exit_status = execute_single_command(mini, commands, cmd_count);
		return (exit_status);
	}
	mini->j = -1;
	while (++mini->j < cmd_count)
		if (fork_and_execute(mini, commands, cmd_count, pipe_fds) != 0)
			return (1);
	if (cmd_count > 1)
	{
		close(pipe_fds[(cmd_count - 2) % 2][0]);
		close(pipe_fds[(cmd_count - 2) % 2][1]);
	}
	exit_status = wait_for_children(cmd_count, mini);
	return (free_all(commands, NULL, cmd_count), exit_status);
}

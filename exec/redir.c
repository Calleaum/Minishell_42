/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:38:04 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/20 19:32:19 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// /* Fonction pour configurer les heredocs */
// static int setup_heredoc(char *delimiter)
// {
// 	int pipe_fd[2];
// 	char *line;
	
// 	if (pipe(pipe_fd) == -1)
// 		return (-1);
	
// 	while (1)
// 	{
// 		ft_putstr_fd("> ", 1);
// 		line = get_next_line(STDIN_FILENO);
// 		if (!line)
// 			break;
		
// 		// Enlever le newline à la fin
// 		if (line[ft_strlen(line) - 1] == '\n')
// 			line[ft_strlen(line) - 1] = '\0';
		
// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
		
// 		ft_putstr_fd(line, pipe_fd[1]);
// 		ft_putstr_fd("\n", pipe_fd[1]);
// 		free(line);
// 	}
	
// 	close(pipe_fd[1]);
// 	return (pipe_fd[0]);
// }

// /* Fonction pour configurer les redirections d'entrée */
// static int setup_input_redirection(t_node *current)
// {
// 	int fd;
// 	t_node *next = current->next;
	
// 	if (!next || !next->data)
// 	{
// 		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
// 		return (-1);
// 	}
	
// 	if (current->type == INPUT_FILE)
// 	{
// 		fd = open(next->data, O_RDONLY);
// 		if (fd == -1)
// 		{
// 			ft_putstr_fd("minishell: ", 2);
// 			ft_putstr_fd(next->data, 2);
// 			ft_putstr_fd(": No such file or directory\n", 2);
// 			return (-1);
// 		}
// 	}
// 	else if (current->type == HEREDOC)
// 	{
// 		fd = setup_heredoc(next->data);
// 		if (fd == -1)
// 			return (-1);
// 	}
// 	else
// 		return (0);
	
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 	{
// 		close(fd);
// 		return (-1);
// 	}
	
// 	close(fd);
// 	return (1);
// }

// /* Fonction pour configurer les redirections de sortie */
// static int setup_output_redirection(t_node *current)
// {
// 	int fd;
// 	int flags;
// 	t_node *next = current->next;
	
// 	if (!next || !next->data)
// 	{
// 		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
// 		return (-1);
// 	}
	
// 	if (current->type == OUTPUT_TRUNC)
// 		flags = O_WRONLY | O_CREAT | O_TRUNC;
// 	else if (current->type == OUTPUT_APPEND)
// 		flags = O_WRONLY | O_CREAT | O_APPEND;
// 	else
// 		return (0);
	
// 	fd = open(next->data, flags, 0644);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(next->data, 2);
// 		ft_putstr_fd(": Permission denied\n", 2);
// 		return (-1);
// 	}
	
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		close(fd);
// 		return (-1);
// 	}
	
// 	close(fd);
// 	return (1);
// }

// /* Fonction pour compter le nombre de commandes séparées par des pipes */
// static int count_commands(t_node *tokens)
// {
// 	int count = 1;
// 	t_node *current = tokens;
	
// 	while (current)
// 	{
// 		if (current->type == PIPE)
// 			count++;
// 		current = current->next;
// 	}
	
// 	return (count);
// }

// /* Fonction pour extraire les commandes de la liste de tokens */
// static t_cmd *extract_commands(t_node *tokens, int cmd_count)
// {
// 	t_cmd *commands = malloc(sizeof(t_cmd) * cmd_count);
// 	t_node *current = tokens;
// 	int cmd_idx = 0;
	
// 	if (!commands)
// 		return (NULL);
	
// 	// Initialiser les commandes
// 	for (int i = 0; i < cmd_count; i++)
// 	{
// 		commands[i].args = NULL;
// 		commands[i].arg_count = 0;
// 		commands[i].start = NULL;
// 		commands[i].end = NULL;
// 	}
	
// 	// Premier nœud de la première commande
// 	commands[cmd_idx].start = current;
	
// 	while (current)
// 	{
// 		if (current->type == PIPE)
// 		{
// 			// Fin de la commande actuelle
// 			commands[cmd_idx].end = current;
// 			cmd_idx++;
			
// 			// Début de la prochaine commande
// 			if (current->next)
// 				commands[cmd_idx].start = current->next;
// 		}
// 		current = current->next;
// 	}
	
// 	// Fin de la dernière commande
// 	commands[cmd_idx].end = NULL;
	
// 	return (commands);
// }

// /* Fonction pour compter les arguments d'une commande */
// static int count_command_args(t_node *start, t_node *end)
// {
// 	int count = 0;
// 	t_node *current = start;
	
// 	while (current && current != end)
// 	{
// 		if (current->type == CMD || current->type == ARG)
// 		{
// 			// Ignorer les redirections et leurs arguments
// 			if (!(current->next && (current->next->type == INPUT_FILE || 
// 								current->next->type == HEREDOC ||
// 								current->next->type == OUTPUT_TRUNC ||
// 								current->next->type == OUTPUT_APPEND)))
// 			{
// 				count++;
// 			}
// 		}
// 		current = current->next;
// 	}
	
// 	return (count);
// }

// /* Fonction pour extraire les arguments d'une commande */
// static char **extract_command_args(t_node *start, t_node *end, int arg_count)
// {
// 	char **args = malloc(sizeof(char *) * (arg_count + 1));
// 	t_node *current = start;
// 	int arg_idx = 0;
	
// 	if (!args)
// 		return (NULL);
	
// 	while (current && current != end && arg_idx < arg_count)
// 	{
// 		if ((current->type == CMD || current->type == ARG) && 
// 			!(current->next && (current->next->type == INPUT_FILE || 
// 							current->next->type == HEREDOC ||
// 							current->next->type == OUTPUT_TRUNC ||
// 							current->next->type == OUTPUT_APPEND)))
// 		{
// 			args[arg_idx++] = ft_strdup(current->data);
// 		}
		
// 		// Sauter les redirections et leurs arguments
// 		if (current->type == INPUT_FILE || current->type == HEREDOC ||
// 			current->type == OUTPUT_TRUNC || current->type == OUTPUT_APPEND)
// 		{
// 			if (current->next)
// 				current = current->next;
// 		}
		
// 		current = current->next;
// 	}
	
// 	args[arg_idx] = NULL;
// 	return (args);
// }

// /* Fonction pour configurer toutes les redirections d'une commande */
// static int setup_redirections(t_node *start, t_node *end)
// {
// 	t_node *current = start;
// 	int result;
	
// 	while (current && current != end)
// 	{
// 		if (current->type == INPUT_FILE || current->type == HEREDOC)
// 		{
// 			result = setup_input_redirection(current);
// 			if (result == -1)
// 				return (-1);
// 			if (result == 1 && current->next)
// 				current = current->next;  // Sauter l'argument de redirection
// 		}
// 		else if (current->type == OUTPUT_TRUNC || current->type == OUTPUT_APPEND)
// 		{
// 			result = setup_output_redirection(current);
// 			if (result == -1)
// 				return (-1);
// 			if (result == 1 && current->next)
// 				current = current->next;  // Sauter l'argument de redirection
// 		}
		
// 		current = current->next;
// 	}
	
// 	return (0);
// }

// /* Fonction pour rechercher le chemin complet d'une commande */
// static char *find_command_path(char *cmd, t_env *env)
// {
// 	char *path_var = NULL;
// 	char **paths = NULL;
// 	char *full_path = NULL;
// 	int i;
	
// 	if (ft_strchr(cmd, '/'))
// 		return (ft_strdup(cmd));
// 	for (i = 0; i < env->count; i++)
// 	{
// 		if (ft_strncmp(env->env_vars[i], "PATH=", 5) == 0)
// 		{
// 			path_var = env->env_vars[i] + 5;
// 			break;
// 		}
// 	}
// 	if (!path_var)
// 		return (NULL);
// 	paths = ft_split(path_var, ':');
// 	if (!paths)
// 		return (NULL);
// 	for (i = 0; paths[i]; i++)
// 	{
// 		char *temp = ft_strjoin(paths[i], "/");
// 		if (!temp)
// 			continue;
// 		full_path = ft_strjoin(temp, cmd);
// 		free(temp);
		
// 		if (!full_path)
// 			continue;
// 		if (access(full_path, X_OK) == 0)
// 		{
// 			for (int j = 0; paths[j]; j++)
// 				free(paths[j]);
// 			free(paths);
// 			return (full_path);
// 		}
// 		free(full_path);
// 		full_path = NULL;
// 	}
// 	for (i = 0; paths[i]; i++)
// 		free(paths[i]);
// 	free(paths);
// 	return (NULL);
// }

// /* Fonction pour exécuter une commande externe */
// static int execute_external_command(t_mini *mini, char **args)
// {
// 	pid_t pid;
// 	int status;
// 	char *cmd_path;
	
// 	cmd_path = find_command_path(args[0], mini->env);
// 	if (!cmd_path)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(args[0], 2);
// 		ft_putstr_fd(": command not found\n", 2);
// 		return (127);
// 	}
	
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		free(cmd_path);
// 		return (1);
// 	}
	
// 	if (pid == 0)
// 	{
// 		execve(cmd_path, args, mini->env->env_vars);
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(args[0], 2);
// 		ft_putstr_fd(": ", 2);
// 		perror("");
// 		exit(126);
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		free(cmd_path);
// 		if (WIFEXITED(status))
// 			return (WEXITSTATUS(status));
// 		return (1);
// 	}
// }

// /* Fonction pour exécuter une commande dans un processus fils */
// static int execute_command(t_mini *mini, t_cmd *cmd)
// {
// 	int status = 0;
	
// 	// Configurer les redirections
// 	if (setup_redirections(cmd->start, cmd->end) == -1)
// 		return (1);
	
// 	// Exécuter la commande en fonction de son type
// 	if (ft_strcmp(cmd->args[0], "echo") == 0)
// 	{
// 		ft_echo(cmd->start);
// 		status = 0;
// 	}
// 	else if (ft_strcmp(cmd->args[0], "cd") == 0)
// 		status = ft_cd(mini, cmd->args);
// 	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
// 		status = ft_pwd(mini);
// 	else if (ft_strcmp(cmd->args[0], "export") == 0)
// 		status = ft_export(mini->env, cmd->start);
// 	else if (ft_strcmp(cmd->args[0], "unset") == 0)
// 		status = ft_unset(mini->env, cmd->start, mini);
// 	else if (ft_strcmp(cmd->args[0], "env") == 0)
// 		status = ft_env(mini, cmd->start);
// 	else if (ft_strcmp(cmd->args[0], "exit") == 0)
// 		ft_exit(mini, cmd->start);
// 	else
// 		status = execute_external_command(mini, cmd->args);
	
// 	return (status);
// }

// /* Fonction pour exécuter un pipeline de commandes */
// static int execute_pipeline(t_mini *mini, t_node *tokens)
// {
// 	int cmd_count = count_commands(tokens);
// 	t_cmd *commands = extract_commands(tokens, cmd_count);
// 	int pipe_fds[2][2];
// 	int in_fd = STDIN_FILENO;
// 	pid_t *pids = malloc(sizeof(pid_t) * cmd_count);
// 	int i, status, last_status = 0;
	
// 	if (!commands || !pids)
// 	{
// 		free(commands);
// 		free(pids);
// 		return (1);
// 	}
// 	for (i = 0; i < cmd_count; i++)
// 	{
// 		commands[i].arg_count = count_command_args(commands[i].start, commands[i].end);
// 		commands[i].args = extract_command_args(commands[i].start, commands[i].end, commands[i].arg_count);
// 		if (!commands[i].args)
// 		{
// 			// Libérer les ressources allouées
// 			// ... (code de nettoyage)
// 			return (1);
// 		}
// 	}
// 	for (i = 0; i < cmd_count; i++)
// 	{
// 		if (i < cmd_count - 1)
// 		{
// 			if (pipe(pipe_fds[i % 2]) == -1)
// 			{
// 				// Gérer l'erreur de pipe
// 				// ... (code de nettoyage)
// 				return (1);
// 			}
// 		}
		
// 		pids[i] = fork();
// 		if (pids[i] == -1)
// 		{
// 			// Gérer l'erreur de fork
// 			// ... (code de nettoyage)
// 			return (1);
// 		}
		
// 		if (pids[i] == 0)
// 		{
// 			// Processus fils
			
// 			// Configurer l'entrée standard à partir du pipe précédent
// 			if (i > 0)
// 			{
// 				if (dup2(in_fd, STDIN_FILENO) == -1)
// 					exit(1);
// 				close(in_fd);
// 			}
			
// 			// Configurer la sortie standard vers le pipe suivant
// 			if (i < cmd_count - 1)
// 			{
// 				if (dup2(pipe_fds[i % 2][1], STDOUT_FILENO) == -1)
// 					exit(1);
// 				close(pipe_fds[i % 2][0]);
// 				close(pipe_fds[i % 2][1]);
// 			}
			
// 			// Exécuter la commande
// 			exit(execute_command(mini, &commands[i]));
// 		}
// 		else
// 		{
// 			// Processus parent
			
// 			// Fermer le descripteur d'entrée précédent
// 			if (i > 0)
// 				close(in_fd);
			
// 			// Fermer l'extrémité d'écriture du pipe courant
// 			if (i < cmd_count - 1)
// 			{
// 				close(pipe_fds[i % 2][1]);
// 				in_fd = pipe_fds[i % 2][0];  // Sauvegarder l'extrémité de lecture pour la prochaine itération
// 			}
// 		}
// 	}
	
// 	// Attendre tous les processus fils
// 	for (i = 0; i < cmd_count; i++)
// 	{
// 		waitpid(pids[i], &status, 0);
// 		if (i == cmd_count - 1)  // Sauvegarder le statut de la dernière commande
// 		{
// 			if (WIFEXITED(status))
// 				last_status = WEXITSTATUS(status);
// 			else
// 				last_status = 1;
// 		}
// 	}
	
// 	// Libérer les ressources
// 	for (i = 0; i < cmd_count; i++)
// 	{
// 		if (commands[i].args)
// 		{
// 			for (int j = 0; j < commands[i].arg_count && commands[i].args[j]; j++)
// 				free(commands[i].args[j]);
// 			free(commands[i].args);
// 		}
// 	}
// 	free(commands);
// 	free(pids);
	
// 	return (last_status);
// }

// /* Fonction principale pour exécuter une ligne de commande */
// int execute_command_line(t_mini *mini, t_node *tokens)
// {
// 	t_node *current = tokens;

// 	while (current)
// 	{
// 		if (current->type == PIPE)
// 			return (execute_pipeline(mini, tokens));
// 		current = current->next;
// 	}
// 	t_cmd cmd;
// 	cmd.start = tokens;
// 	cmd.end = NULL;
// 	cmd.arg_count = count_command_args(tokens, NULL);
// 	cmd.args = extract_command_args(tokens, NULL, cmd.arg_count);
// 	if (!cmd.args || !cmd.args[0])
// 	{
// 		if (cmd.args)
// 		{
// 			for (int i = 0; i < cmd.arg_count && cmd.args[i]; i++)
// 				free(cmd.args[i]);
// 			free(cmd.args);
// 		}
// 		return (0);
// 	}
// 	int status;
// 	if (ft_strcmp(cmd.args[0], "cd") == 0 ||
// 		ft_strcmp(cmd.args[0], "export") == 0 ||
// 		ft_strcmp(cmd.args[0], "unset") == 0 ||
// 		ft_strcmp(cmd.args[0], "exit") == 0)
// 	{
// 		if (setup_redirections(cmd.start, cmd.end) == -1)
// 		{
// 			for (int i = 0; i < cmd.arg_count && cmd.args[i]; i++)
// 				free(cmd.args[i]);
// 			free(cmd.args);
// 			return (1);
// 		}
// 		if (ft_strcmp(cmd.args[0], "cd") == 0)
// 			status = ft_cd(mini, cmd.start);
// 		else if (ft_strcmp(cmd.args[0], "export") == 0)
// 			status = ft_export(mini->env, cmd.start);
// 		else if (ft_strcmp(cmd.args[0], "unset") == 0)
// 			status = ft_unset(mini->env, cmd.start, mini);
// 		else if (ft_strcmp(cmd.args[0], "exit") == 0)
// 			ft_exit(mini, cmd.start);
// 		else
// 			status = 1;  // Ne devrait jamais arriver
// 	}
// 	else
// 	{
// 		pid_t pid = fork();
		
// 		if (pid == -1)
// 		{
// 			for (int i = 0; i < cmd.arg_count && cmd.args[i]; i++)
// 				free(cmd.args[i]);
// 			free(cmd.args);
// 			return (1);
// 		}
// 		if (pid == 0)
// 		{
// 			int result = execute_command(mini, &cmd);
// 			exit(result);
// 		}
// 		else
// 		{
// 			int child_status;
// 			waitpid(pid, &child_status, 0);
			
// 			if (WIFEXITED(child_status))
// 				status = WEXITSTATUS(child_status);
// 			else
// 				status = 1;
// 		}
// 	}
// 	for (int i = 0; i < cmd.arg_count && cmd.args[i]; i++)
// 		free(cmd.args[i]);
// 	free(cmd.args);
	
// 	return (status);
// }

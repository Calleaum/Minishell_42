
// Opens input file for redirection
// static int handle_input_file(char *filename)
// {
// 	int fd;
	
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(filename, 2);
// 		ft_putstr_fd(": ", 2);
// 		perror("");
// 		return (-1);
// 	}
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 	{
// 		close(fd);
// 		perror("minishell: dup2");
// 		return (-1);
// 	}
// 	close(fd);
// 	return (0);
// }

// // Opens output file for truncation redirection
// static int handle_output_trunc(char *filename)
// {
// 	int fd;
	
// 	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(filename, 2);
// 		ft_putstr_fd(": ", 2);
// 		perror("");
// 		return (-1);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		close(fd);
// 		perror("minishell: dup2");
// 		return (-1);
// 	}
// 	close(fd);
// 	return (0);
// }

// // Opens output file for append redirection
// static int handle_output_append(char *filename)
// {
// 	int fd;
	
// 	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(filename, 2);
// 		ft_putstr_fd(": ", 2);
// 		perror("");
// 		return (-1);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		close(fd);
// 		perror("minishell: dup2");
// 		return (-1);
// 	}
// 	close(fd);
// 	return (0);
// }

// // Handles heredoc redirection
// static int handle_heredoc(char *delimiter, t_mini *mini)
// {
//     int     pipe_fds[2];
//     char    *line;
//     char    *expanded_line;
    
//     if (pipe(pipe_fds) == -1)
//     {
//         perror("minishell: pipe");
//         return (-1);
//     }
//     while (1)
//     {
//         ft_putstr_fd("> ", 1);
//         line = get_next_line(0); // Assuming you have get_next_line function
//         if (!line)
//             break;
//         // Remove newline character if present
//         if (line[ft_strlen(line) - 1] == '\n')
//             line[ft_strlen(line) - 1] = '\0';
//         if (ft_strcmp(line, delimiter) == 0)
//         {
//             free(line);
//             break;
//         }
//         // Expand variables in heredoc line if not single quoted delimiter
//         if (ft_strchr(delimiter, '\'') == NULL)
//         {
//             expanded_line = expand_variables(line, mini->last_exit_status, mini->env);
//             free(line);
//             line = expanded_line;
//         }
//         ft_putstr_fd(line, pipe_fds[1]);
//         ft_putstr_fd("\n", pipe_fds[1]);
//         free(line);
//     }
//     close(pipe_fds[1]);
//     if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
//     {
//         close(pipe_fds[0]);
//         perror("minishell: dup2");
//         return (-1);
//     }
//     close(pipe_fds[0]);
//     return (0);
// }

// // Applies all redirections in a command
// static int apply_redirections(t_node *tokens, t_mini *mini)
// {
// 	t_node *current;
// 	int result;
	
// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type == INPUT_FILE && current->next)
// 		{
// 			result = handle_input_file(current->next->data);
// 			if (result == -1)
// 				return (1);
// 			current = current->next;
// 		}
// 		else if (current->type == OUTPUT_TRUNC && current->next)
// 		{
// 			result = handle_output_trunc(current->next->data);
// 			if (result == -1)
// 				return (1);
// 			current = current->next;
// 		}
// 		else if (current->type == OUTPUT_APPEND && current->next)
// 		{
// 			result = handle_output_append(current->next->data);
// 			if (result == -1)
// 				return (1);
// 			current = current->next;
// 		}
// 		else if (current->type == HEREDOC && current->next)
// 		{
// 			result = handle_heredoc(current->next->data, mini);
// 			if (result == -1)
// 				return (1);
// 			current = current->next;
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }

// // Extracts command and arguments from token list
// static char **extract_command_args(t_node *tokens)
// {
// 	t_node *current;
// 	int count;
// 	char **args;
// 	int i;
	
// 	// Count CMD and ARG tokens
// 	count = 0;
// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type == CMD || current->type == ARG)
// 			count++;
// 		current = current->next;
// 	}
	
// 	// Allocate memory for args array
// 	args = (char **)malloc(sizeof(char *) * (count + 1));
// 	if (!args)
// 		return (NULL);
	
// 	// Fill args array
// 	i = 0;
// 	current = tokens;
// 	while (current && i < count)
// 	{
// 		if (current->type == CMD || current->type == ARG)
// 		{
// 			args[i] = ft_strdup(current->data);
// 			if (!args[i])
// 			{
// 				// Free previously allocated strings
// 				while (--i >= 0)
// 					free(args[i]);
// 				free(args);
// 				return (NULL);
// 			}
// 			i++;
// 		}
// 		current = current->next;
// 	}
// 	args[i] = NULL;
// 	return (args);
// }

// // Creates a copy of a token list from start to end (not including end)
// static t_node *copy_token_list(t_node *start, t_node *end)
// {
// 	t_node *head;
// 	t_node *current;
// 	t_node *new_token;
	
// 	head = NULL;
// 	current = start;
// 	while (current && current != end)
// 	{
// 		new_token = create_token(current->data, current->type);
// 		if (!new_token)
// 		{
// 			free_list(head);
// 			return (NULL);
// 		}
// 		add_token(&head, new_token);
// 		current = current->next;
// 	}
// 	return (head);
// }

// // Split token list at pipe symbols
// static t_node **split_commands(t_node *tokens, int *cmd_count)
// {
// 	t_node **commands;
// 	t_node *current;
// 	t_node *start;
// 	int count;
// 	int i;
	
// 	// Count the number of pipes + 1
// 	count = 1;
// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type == PIPE)
// 			count++;
// 		current = current->next;
// 	}
	
// 	// Allocate memory for commands array
// 	commands = (t_node **)malloc(sizeof(t_node *) * count);
// 	if (!commands)
// 		return (NULL);
	
// 	// Split the tokens at each pipe
// 	i = 0;
// 	current = tokens;
// 	start = current;
// 	while (current)
// 	{
// 		if (current->type == PIPE)
// 		{
// 			// Create a sublist from start to current (excluding pipe)
// 			commands[i] = copy_token_list(start, current);
// 			if (!commands[i])
// 			{
// 				// Free previously allocated lists
// 				while (--i >= 0)
// 					free_list(commands[i]);
// 				free(commands);
// 				return (NULL);
// 			}
// 			i++;
// 			start = current->next;
// 		}
// 		current = current->next;
// 	}
	
// 	// Handle the last command after the last pipe (or the only command if no pipes)
// 	if (start)
// 	{
// 		commands[i] = copy_token_list(start, NULL);
// 		if (!commands[i])
// 		{
// 			while (i >= 0)
// 				free_list(commands[i]);
// 			free(commands);
// 			return (NULL);
// 		}
// 	}
	
// 	*cmd_count = count;
// 	return (commands);
// }

// // Executes a builtin command
// static int execute_builtin(t_mini *mini, t_node *tokens)
// {
// 	if (!ft_strcmp(tokens->data, "echo"))
// 		ft_echo(tokens->next);
// 	else if (!ft_strcmp(tokens->data, "cd"))
// 		return (ft_cd(mini, tokens));
// 	else if (!ft_strcmp(tokens->data, "pwd"))
// 		return (ft_pwd(mini));
// 	else if (!ft_strcmp(tokens->data, "export"))
// 		return (ft_export(mini, tokens));
// 	else if (!ft_strcmp(tokens->data, "unset"))
// 		return (ft_unset(mini, tokens));
// 	else if (!ft_strcmp(tokens->data, "env"))
// 		return (ft_env(mini, tokens));
// 	else if (!ft_strcmp(tokens->data, "exit"))
// 		ft_exit(mini, tokens);
	
// 	return (0);
// }

// // Checks if command is a builtin
// static int is_builtin(char *cmd)
// {
// 	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") ||
// 			!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") ||
// 			!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
// 			!ft_strcmp(cmd, "exit"));
// }

// // Helper function to find the path of a command
// static char *find_command_path(char *cmd, t_mini *mini)
// {
// 	char *path_env;
// 	char **paths;
// 	char *full_path;
// 	int i;
	
// 	// Check if cmd contains a slash (absolute or relative path)
// 	if (ft_strchr(cmd, '/'))
// 	{
// 		if (access(cmd, F_OK | X_OK) == 0)
// 			return (ft_strdup(cmd));
// 		return (NULL);
// 	}
	
// 	// Get PATH environment variable
// 	path_env = get_env_value(mini->env, "PATH");
// 	if (!path_env)
// 		return (NULL);
	
// 	// Split PATH into individual directories
// 	paths = ft_split(path_env, ':');
// 	if (!paths)
// 		return (NULL);
	
// 	// Try each directory in PATH
// 	i = 0;
// 	while (paths[i])
// 	{
// 		full_path = ft_strjoin3(paths[i], "/", cmd);
// 		if (!full_path)
// 		{
// 			// Free paths array
// 			for (int j = 0; paths[j]; j++)
// 				free(paths[j]);
// 			free(paths);
// 			return (NULL);
// 		}
		
// 		if (access(full_path, F_OK | X_OK) == 0)
// 		{
// 			// Free paths array
// 			for (int j = 0; paths[j]; j++)
// 				free(paths[j]);
// 			free(paths);
// 			return (full_path);
// 		}
		
// 		free(full_path);
// 		i++;
// 	}
	
// 	// Free paths array
// 	for (i = 0; paths[i]; i++)
// 		free(paths[i]);
// 	free(paths);
	
// 	return (NULL);
// }

// // Executes an external command
// static int execute_external_command(t_mini *mini, char **args)
// {
// 	char *path;
// 	pid_t pid;
// 	int status;
	
// 	path = find_command_path(args[0], mini);
// 	if (!path)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(args[0], 2);
// 		ft_putstr_fd(": command not found\n", 2);
// 		return (127);
// 	}
	
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("minishell: fork");
// 		free(path);
// 		return (1);
// 	}
// 	else if (pid == 0)
// 	{
// 		// Child process
// 		if (execve(path, args, mini->env->env_vars) == -1)
// 		{
// 			perror("minishell: execve");
// 			exit(1);
// 		}
// 	}
// 	else
// 	{
// 		// Parent process
// 		waitpid(pid, &status, 0);
// 		free(path);
// 		if (WIFEXITED(status))
// 			return (WEXITSTATUS(status));
// 		else
// 			return (1);
// 	}
// 	return (0);
// }

// // Main function to handle pipes and execute commands
// int execute_pipeline(t_mini *mini, t_node *tokens)
// {
// 	int cmd_count;
// 	t_node **commands;
// 	int i;
// 	int pipe_fds[2][2];
// 	pid_t pid;
// 	int status;
// 	int exit_status;
	
// 	// Split the token list into separate commands
// 	commands = split_commands(tokens, &cmd_count);
// 	if (!commands)
// 		return (1);
	
// 	// No need to fork if there's only one command and it's a builtin
// 	if (cmd_count == 1 && commands[0] && commands[0]->type == CMD)
// 	{
// 		// Save original stdin and stdout
// 		int stdin_copy = dup(STDIN_FILENO);
// 		int stdout_copy = dup(STDOUT_FILENO);
		
// 		// Apply redirections
// 		if (apply_redirections(commands[0], mini) != 0)
// 		{
// 			// Restore original stdin and stdout
// 			dup2(stdin_copy, STDIN_FILENO);
// 			dup2(stdout_copy, STDOUT_FILENO);
// 			close(stdin_copy);
// 			close(stdout_copy);
			
// 			// Free allocated memory
// 			free_list(commands[0]);
// 			free(commands);
// 			return (1);
// 		}
		
// 		// Execute builtin
// 		exit_status = execute_builtin(mini, commands[0]);
		
// 		// Restore original stdin and stdout
// 		dup2(stdin_copy, STDIN_FILENO);
// 		dup2(stdout_copy, STDOUT_FILENO);
// 		close(stdin_copy);
// 		close(stdout_copy);
		
// 		// Free allocated memory
// 		free_list(commands[0]);
// 		free(commands);
		
// 		return (exit_status);
// 	}
	
// 	// Execute commands with pipes
// 	for (i = 0; i < cmd_count; i++)
// 	{
// 		// Create pipe for next command (if not last command)
// 		if (i < cmd_count - 1)
// 		{
// 			if (pipe(pipe_fds[i % 2]) == -1)
// 			{
// 				perror("minishell: pipe");
// 				// Free remaining commands
// 				while (i < cmd_count)
// 					free_list(commands[i++]);
// 				free(commands);
// 				return (1);
// 			}
// 		}
		
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("minishell: fork");
// 			// Close pipes and free remaining commands
// 			close(pipe_fds[i % 2][0]);
// 			close(pipe_fds[i % 2][1]);
// 			while (i < cmd_count)
// 				free_list(commands[i++]);
// 			free(commands);
// 			return (1);
// 		}
// 		else if (pid == 0)
// 		{
// 			// Child process
			
// 			// Connect to previous pipe's read end (if not first command)
// 			if (i > 0)
// 			{
// 				if (dup2(pipe_fds[(i - 1) % 2][0], STDIN_FILENO) == -1)
// 				{
// 					perror("minishell: dup2");
// 					exit(1);
// 				}
// 				close(pipe_fds[(i - 1) % 2][0]);
// 				close(pipe_fds[(i - 1) % 2][1]);
// 			}
			
// 			// Connect to current pipe's write end (if not last command)
// 			if (i < cmd_count - 1)
// 			{
// 				if (dup2(pipe_fds[i % 2][1], STDOUT_FILENO) == -1)
// 				{
// 					perror("minishell: dup2");
// 					exit(1);
// 				}
// 				close(pipe_fds[i % 2][0]);
// 				close(pipe_fds[i % 2][1]);
// 			}
			
// 			// Apply redirections
// 			if (apply_redirections(commands[i], mini) != 0)
// 				exit(1);
			
// 			// Execute command
// 			if (commands[i] && commands[i]->type == CMD)
// 			{
// 				if (is_builtin(commands[i]->data))
// 				{
// 					exit(execute_builtin(mini, commands[i]));
// 				}
// 				else
// 				{
// 					char **args = extract_command_args(commands[i]);
// 					if (!args)
// 						exit(1);
					
// 					exit_status = execute_external_command(mini, args);
					
// 					// Free args
// 					for (int j = 0; args[j]; j++)
// 						free(args[j]);
// 					free(args);
					
// 					exit(exit_status);
// 				}
// 			}
// 			else if (commands[i] && commands[i]->type == ARG)
// 			{
// 				// Command is just an argument, treat it as external command
// 				char **args = extract_command_args(commands[i]);
// 				if (!args)
// 					exit(1);
				
// 				exit_status = execute_external_command(mini, args);
				
// 				// Free args
// 				for (int j = 0; args[j]; j++)
// 					free(args[j]);
// 				free(args);
				
// 				exit(exit_status);
// 			}
// 			else
// 			{
// 				// Empty command or unknown type
// 				exit(0);
// 			}
// 		}
		
// 		// Parent process
		
// 		// Close previous pipe's read and write ends
// 		if (i > 0)
// 		{
// 			close(pipe_fds[(i - 1) % 2][0]);
// 			close(pipe_fds[(i - 1) % 2][1]);
// 		}
// 	}
	
// 	// Close the last pipe if there was one
// 	if (cmd_count > 1)
// 	{
// 		close(pipe_fds[(cmd_count - 2) % 2][0]);
// 		close(pipe_fds[(cmd_count - 2) % 2][1]);
// 	}
	
// 	// Wait for all child processes
// 	exit_status = 0;
// 	for (i = 0; i < cmd_count; i++)
// 	{
// 		waitpid(-1, &status, 0);
// 		if (WIFEXITED(status))
// 		{
// 			exit_status = WEXITSTATUS(status);
// 		}
// 		else if (WIFSIGNALED(status))
// 		{
// 			exit_status = 128 + WTERMSIG(status);
// 		}
// 	}
	
// 	// Free all commands
// 	for (i = 0; i < cmd_count; i++)
// 		free_list(commands[i]);
// 	free(commands);
	
// 	// Set last exit status
// 	mini->last_exit_status = exit_status;
	
// 	return (exit_status);
// }
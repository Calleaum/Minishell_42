/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:35:37 by lgrisel           #+#    #+#             */
/*   Updated: 2025/01/29 14:10:07 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
	return (NULL);
}

static void	exec(char *cmd, char **envp)
{
	char	**paths;
	char	**args;
	char	*full_path;
	int		i;

	paths = ft_split(get_path(envp), ':');
	args = ft_split(cmd, ' ');
	i = -1;
	if (!paths || !args)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(cmd, 2);
		exit(127);
	}
	while (paths[++i])
	{
		full_path = ft_strjoin(ft_strjoin(paths[i], "/"), args[0]);
		if (access(full_path, X_OK) == 0)
			execve(full_path, args, envp);
		free(full_path);
	}
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putendl_fd(cmd, 2);
	exit(127);
}

static void	kinder(char **argv, char **envp, int *pipefd)
{
	int	fd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		perror("open infile");
		exit(1);
	}
	dup2(fd, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	exec(argv[2], envp);
}

static void	kinder2(char **argv, char **envp, int *pipefd)
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("open outfile");
		exit(1);
	}
	dup2(pipefd[0], 0);
	dup2(fd, 1);
	close(pipefd[1]);
	exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (ft_printf("\e[31mError: Bad arguments \e[0m"),
			ft_printf("\e[32mEx:./pipex <file1> <cmd1> <cmd2> <file2>\n\e[0m"),
			0);
	if (pipe(pipefd) == -1)
		exit(1);
	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (pid1 == 0)
		kinder(argv, envp, pipefd);
	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	if (pid2 == 0)
		kinder2(argv, envp, pipefd);
	return (close(pipefd[0]), close(pipefd[1]),
		waitpid(pid1, NULL, 0), waitpid(pid2, NULL, 0), 0);
}

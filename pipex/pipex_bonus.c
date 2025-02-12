/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:10:52 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/04 12:17:58 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	read_limiter(char *limiter, int write_fd)
{
	char	*line;

	while (get_next_line(&line))
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(line) - 1 == ft_strlen(limiter))
		{
			free(line);
			exit(0);
		}
		write(write_fd, line, ft_strlen(line));
		free(line);
	}
}

static void	here_doc(char *limiter, int argc)
{
	int		fd[2];
	pid_t	reader;

	if (argc < 6)
		usage();
	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		read_limiter(limiter, fd[1]);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(NULL);
}

static void	child_process(t_pipe *pip, int filein, int fileout, int *fd)
{
	if (pip->start < pip->end)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else
		dup2(fileout, STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	if (filein != STDIN_FILENO)
		close(filein);
	if (pip->start < pip->end)
		close(fd[0]);
	exec(pip->argv[pip->start], pip->envp);
}

static void	handle_pipe(t_pipe *pip, int filein, int fileout)
{
	int		pipefd[2];
	pid_t	pid;

	init_fd(pipefd);
	if (pip->start > pip->end)
		return ;
	if (pip->start < pip->end && pipe(pipefd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		child_process(pip, filein, fileout, pipefd);
	if (filein != STDIN_FILENO)
		close(filein);
	if (pip->start < pip->end)
		close(pipefd[1]);
	pip->start++;
	if (pip->start <= pip->end)
		handle_pipe(pip, pipefd[0], fileout);
	else if (pipefd[0] != -1)
		close(pipefd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	int		filein;
	int		fileout;
	t_pipe	pipe;

	if (argc < 5)
		usage();
	pipe.argv = argv;
	pipe.envp = envp;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0
		&& 8 == ft_strlen(argv[1]))
	{
		init(&pipe, 1, argc);
		fileout = open_file(argv[argc - 1], 0);
		here_doc(argv[2], argc);
		handle_pipe(&pipe, STDIN_FILENO, fileout);
	}
	else
	{
		init(&pipe, 0, argc);
		filein = open_file(argv[1], 2);
		fileout = open_file(argv[argc - 1], 1);
		handle_pipe(&pipe, filein, fileout);
	}
	while (wait(NULL) > 0)
		;
}

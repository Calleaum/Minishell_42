/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:14:11 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/04 12:18:17 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	exec(char *cmd, char **envp)
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

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
	{
		perror("Error");
		exit(1);
	}
	return (file);
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	return (r);
}

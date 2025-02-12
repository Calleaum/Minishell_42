/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:53:31 by lgrisel           #+#    #+#             */
/*   Updated: 2024/11/26 15:53:31 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_line(char *line_buffer)
{
	char	*rest;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	rest = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*rest == '\0')
	{
		free(rest);
		rest = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (rest);
}

static char	*get_line(int fd, char *rest, char *buffer)
{
	ssize_t	bytes_readed;
	char	*tmp;

	bytes_readed = 1;
	while (bytes_readed > 0)
	{
		bytes_readed = read(fd, buffer, BUFFER_SIZE);
		if (bytes_readed == -1)
			return (free(rest), NULL);
		else if (bytes_readed == 0)
			break ;
		buffer[bytes_readed] = '\0';
		if (!rest)
			rest = ft_strdup("");
		tmp = rest;
		rest = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = get_line(fd, rest, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	rest = set_line(line);
	return (line);
}

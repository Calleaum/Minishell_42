# Minishell
oui

https://docs.google.com/spreadsheets/d/1TSIy1p9VGYE3IVhU66jqAkYDFCMEiaL4nX72kP2c8aA/edit?usp=drive_link


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
​
int 	ft_check_line(char *dest)
{
	int i = 0;
	if (!dest)
		return (0);
	while(dest[i] && dest[i] != '\n')
		i++;
	if (dest[i] == '\n')
		return(1);
	return(0);
}
​
int	ft_strlen_line(char *dest)
{
	int i = 0;
	if (!dest)
		return (0);
	while(dest[i] && dest[i] != '\n')
		i++;
	return(i);
}
​
int	ft_strlen(char *dest)
{
	int i = 0;
	if (!dest)
		return (0);
	while(dest[i])
		i++;
	return(i);
}
​
char	*ft_join_line(char *src, char *buff)
{
	int i = 0;
	int j = 0;
	char *dest;
	
	if (!src)
		dest = malloc(sizeof(char) * ft_strlen_line(buff) + 2);
	else
	{
		dest = malloc(sizeof(char) * ft_strlen_line(buff) + ft_strlen(src) + 2);
		while(src[i])
		{
			dest[i] = src[i];
			i++;
		}
		free(src);
	}
	while(buff[j] && buff[j] != '\n')
	{
		dest[i] = buff[j];
		i++;
		j++;
	}
	dest[i] = '\n';
	if (buff[j] == '\n')
		i++;
	dest[i] = '\0';
	if (dest[0] == '\0')
	{
		free(dest);
		return(NULL);
	}
	return(dest);
}
​
void	ft_cute_line(char *dest)
{
	int  i = 0;
	int j = 0;
	while(dest[i] && dest[i] != '\n')
		i++;
	if (dest[i] == '\n')
		i++;
	while (dest[i])
	{
		dest[j] = dest[i];
		i++;
		j++;
	}
	dest[j] = '\0';
}
​
char	*get_next_line(int fd)
{
	static char buff[BUFFER_SIZE + 1];
	int i = 1;
	char *dest = NULL;
	
	if (BUFFER_SIZE <= 0 || fd < 0)
		return(NULL);
	if (ft_check_line(buff) == 1)
	{
		ft_cute_line(buff);
		dest = ft_join_line(dest, buff);
	}
	while (i > 0 && ft_check_line(buff) == 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i <= 0)
			return(dest);
		buff[i] = '\0';
		dest = ft_join_line(dest, buff);
	}
	return(dest);
}
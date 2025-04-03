/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:08:02 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/03 19:28:41 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	result = malloc(len1 + len2 + len3 + 1);
	if (!result)
		return (NULL);
	ft_strcpy2(result, s1);
	ft_strcpy2(result + len1, s2);
	ft_strcpy2(result + len1 + len2, s3);
	return (result);
}

char	*ft_strcpy2(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	init_mini(t_mini *mini, char **envp)
{
	mini->str = NULL;
	mini->exp = NULL;
	mini->last_exit_status = 0;
	mini->count = 0;
	mini->in_word = 0;
	mini->quote = '\0';
	mini->env = init_env(envp);
	if (!mini->env)
	{
		printf("Error initializing environment.\n");
		exit(1);
	}
}

int	handle_cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

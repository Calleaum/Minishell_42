/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:12:03 by lgrisel           #+#    #+#             */
/*   Updated: 2024/10/19 14:12:03 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = 0;
	i = 0;
	while (s[len] && len < n)
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

static char	*next_word(const char **s, char c)
{
	const char	*start;
	size_t		length;

	while (**s == c && **s)
	{
		(*s)++;
	}
	start = *s;
	while (**s && **s != c)
	{
		(*s)++;
	}
	length = *s - start;
	return (ft_strndup(start, length));
}

char	**ft_split(char const *s, char c)
{
	int		count_word;
	char	**result;
	int		i;
	char	*word;

	if (!s)
		return (NULL);
	count_word = count_words(s, c);
	result = malloc(sizeof(char *) * (count_word + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		word = next_word(&s, c);
		if (*word)
			result[i++] = word;
		else
			free (word);
	}
	result[i] = NULL;
	return (result);
}
/*
#include <stdio.h>
int main(void)
{
    char **result = ft_split("bonjour coucou salut", ' ');
	int i = 0;
    while (result[i])
		{
        printf("%s\n", result[i]);
        free(result[i]);
		i++;
    }
    free(result);
    return 0;
}*/
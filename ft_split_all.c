/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:19:32 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/17 08:37:29 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return ((c == ' ' || (c >= 9 && c <= 13)));
}

static int	count_words(const char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (!is_space(*str))
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*extract_word(const char **str)
{
	const char	*start;
	char		*word;
	int			length;
	int			i;

	length = 0;
	while (is_space(**str))
		(*str)++;
	start = *str;
	while (**str && !is_space(**str))
	{
		length++;
		(*str)++;
	}
	word = (char *)malloc(length + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < length)
	{
		word[i] = start[i];
		i++;
	}
	word[length] = '\0';
	return (word);
}

static void	free_all(char **result, int i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
}

char	**ft_split_all(const char *str)
{
	int		words;
	char	**result;
	int		i;

	if (!str)
		return (NULL);
	words = count_words(str);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*str && i < words)
	{
		while (is_space(*str))
			str++;
		if (*str)
		{
			result[i] = extract_word(&str);
			if (!result[i])
    			return (free_all(result, i), NULL);
			i++;
		}
		else if (*str)
			return (free_all(result, i), NULL);
	}
	result[i] = NULL;
	return (result);
}

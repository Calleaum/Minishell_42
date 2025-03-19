/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:19:32 by lgrisel           #+#    #+#             */
/*   Updated: 2025/03/13 17:09:36 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_words(const char *s, t_mini *split)
{
	split->count = 0;
	split->in_word = 0;
	split->quote = 0;
	while (*s)
	{
		if (*s == '"' || *s == '\'')
		{
			if (!split->quote)
				split->quote = *s;
			else if (split->quote == *s)
				split->quote = 0;
		}
		else if (ft_isspace(*s) && !split->quote)
			split->in_word = 0;
		else if (!split->in_word)
		{
			split->in_word = 1;
			split->count++;
		}
		s++;
	}
	if (split->quote)
		return (ft_putendl_fd("Error: Unclosed quote detected", 2), -1);
	return (split->count);
}

char	*copy_word(const char **s, t_mini *split)
{
	char	*dst;
	char	*word;

	split->quote = 0;
	word = malloc(ft_strlen(*s) + 1);
	if (!word)
		return (NULL);
	dst = word;
	while (**s && (split->quote || !ft_isspace(**s)))
	{
		if (**s == '"' || **s == '\'')
		{
			if (!split->quote)
				split->quote = **s;
			else if (split->quote == **s)
				split->quote = 0;
			else
				*dst++ = **s;
			(*s)++;
			continue ;
		}
		*dst++ = *(*s)++;
	}
	*dst = '\0';
	return (word);
}

char	**ft_split_all(const char *s)
{
	t_mini	split;
	size_t	words;
	size_t	i;
	char	**result;

	if (!s)
		return (NULL);
	words = count_words(s, &split);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (*s)
			result[i++] = copy_word(&s, &split);
	}
	result[i] = NULL;
	return (result);
}

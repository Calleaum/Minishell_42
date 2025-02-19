/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:19:32 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/19 13:14:13 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return ((c == ' ' || (c >= 9 && c <= 13)));
}

static int	count_words(const char *str, t_split *split)
{
	split->count = 0;
	split->in_word = 0;
	split->in_quote = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			split->in_quote = !split->in_quote;
			if (!split->in_word)
			{
				split->count++;
				split->in_word = 1;
			}
		}
		else if ((!is_space(*str) || split->in_quote) && !split->in_word)
		{
			split->count++;
			split->in_word = 1;
		}
		else
			split->in_word = 0;
		str++;
	}
	return (split->count);
}

static char	*extract_word(const char **str, t_split *split)
{
	char		*word;

	split->length = 0;
	split->in_quote = 0;
	split->i = 0;
	while (is_space(**str))
		(*str)++;
	split->start = *str;
	while (**str && (!is_space(**str) || split->in_quote))
	{
		if (**str == '"' || **str == '\'')
			split->in_quote = !split->in_quote;
		split->length++;
		(*str)++;
	}
	word = (char *)malloc(split->length + 1);
	if (!word)
		return (NULL);
	while (split->i < split->length)
	{
		word[split->i] = split->start[split->i];
		split->i++;
	}
	word[split->length] = '\0';
	return (word);
}

char	**ft_split_all(const char *str)
{
	t_split	split;
	int		count_word;
	char	**result;
	int		i;

	if (!str)
		return (NULL);
	count_word = count_words(str, &split);
	result = (char **)malloc(sizeof(char *) * (count_word + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*str && i < count_word)
	{
		while (is_space(*str))
			str++;
		if (*str)
		{
			result[i] = extract_word(&str, &split);
			i++;
		}
	}
	result[i] = NULL;
	return (result);
}

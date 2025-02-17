/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:19:32 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/17 17:01:50 by calleaum         ###   ########.fr       */
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

char	**ft_split_all(const char *str)
{
	int		count_word;
	char	**result;
	int		i;

	if (!str)
		return (NULL);
	count_word = count_words(str);
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
			result[i] = extract_word(&str);
			i++;
		}
	}
	result[i] = '\0';
	return (result);
}

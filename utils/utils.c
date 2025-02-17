/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:10:17 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/17 15:58:32 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_space(t_mini *mini)
{
	int	i;

	i = 0;
	while (is_space(mini->str[i]))
		if (mini->str[i] == '\n' || mini->str[++i] == '\n')
			return (1);
	return (0);
}

size_t	strlenus(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !is_space(str[i]))
		i++;
	return (i);
}

size_t	strlenws(char *str)
{
		size_t	i;

	i = 0;
	while (ft_isalpha(str[i]))
		i++;
	while (is_space(str[i]) && str[i] != '\n')
		i++;
	return (i);
}

int	isdigit_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	count_words_skipall(const char *s)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (!is_space(*s) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_space(*s))
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:54:25 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/17 11:07:01 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_n_option(char *str, int *i)
{
	int	newline;
	int	j;

	newline = 1;
	while (str[*i] == '-' && str[*i + 1] == 'n')
	{
		j = *i + 1;
		while (str[j] == 'n')
			j++;
		if (str[j] == ' ' || str[j] == '\0')
		{
			newline = 0;
			*i = j;
			while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
				(*i)++;
		}
		else
			break ;
	}
	return (newline);
}

void	print_words_with_spaces(char *str, int *i)
{
	int	first_word;

	first_word = 1;
	while (str[*i])
	{
		if (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		{
			if (!first_word)
				write(1, " ", 1);
			while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
				(*i)++;
		}
		else if (str[*i] == '\\' && str[*i + 1] != '\0'
			&& str[*i + 1] != ' ' && str[*i + 1] != '\n')
		{
			write(1, &str[*i + 1], 1);
			(*i) += 2;
		}
		else
		{
			write(1, &str[*i], 1);
			first_word = 0;
			(*i)++;
		}
	}
}

void	ft_echo(char *str)
{
	int	i;
	int	newline;

	i = 4;
	newline = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	newline = handle_n_option(str, &i);
	print_words_with_spaces(str, &i);
	if (newline)
		write(1, "\n", 1);
}

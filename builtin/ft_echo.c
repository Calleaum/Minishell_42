/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:54:25 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/25 17:13:54 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_n_option(t_node **args)
{
	int		newline;
	t_node	*current;
	int		j;

	newline = 1;
	current = *args;
	while (current && current->data[0] == '-'
		&& current->data[1] == 'n')
	{
		j = 1;
		while (current->data[j] == 'n')
			j++;
		if (current->data[j] == '\0')
		{
			newline = 0;
			*args = current->next;
		}
		else
			break ;
		current = *args;
	}
	return (newline);
}

static void	print_words_with_spaces_linked(t_node *args)
{
	int		first_word;

	first_word = 1;
	while (args)
	{
		if (!first_word)
			write(1, " ", 1);
		write(1, args->data, ft_strlen(args->data));
		first_word = 0;
		args = args->next;
	}
}

void	ft_echo(t_mini *mini, t_node *args)
{
	int	newline;

	if (!args)
	{
		write(1, "\n", 1);
		return ;
	}
	newline = handle_n_option(&args);
	print_words_with_spaces_linked(args);
	mini->last_exit_status = 0;
	if (newline)
		write(1, "\n", 1);
}

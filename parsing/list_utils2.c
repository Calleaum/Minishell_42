/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:58:19 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/15 17:58:28 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_token_type(char *word, t_mini *t)
{
	if (t->special)
	{
		t->special = 0;
		return (ARG);
	}
	if (!ft_strncmp(word, "<", INT_MAX))
		return (IF);
	if (!ft_strncmp(word, "<<", INT_MAX))
		return (HD);
	if (!ft_strncmp(word, ">", INT_MAX))
		return (OT);
	if (!ft_strncmp(word, ">>", INT_MAX))
		return (OA);
	if (!ft_strncmp(word, "|", INT_MAX))
		return (PIPE);
	if (!ft_strncmp(word, "echo", INT_MAX)
		|| !ft_strncmp(word, "cd", INT_MAX)
		|| !ft_strncmp(word, "pwd", INT_MAX)
		|| !ft_strncmp(word, "exit", INT_MAX)
		|| !ft_strncmp(word, "export", INT_MAX)
		|| !ft_strncmp(word, "env", INT_MAX)
		|| !ft_strncmp(word, "unset", INT_MAX))
		return (CMD);
	return (ARG);
}

char	*process_quoted_section(char *input, int *i, char quote_char)
{
	int		start;
	int		end;
	char	*result;

	start = *i + 1;
	end = start;
	while (input[end] && input[end] != quote_char)
		end++;
	if (input[end] != quote_char)
		start -= 1;
	result = (char *)malloc(end - start + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, input + start, end - start + 1);
	if (input[end] != quote_char)
		*i = end;
	else
		*i = end + 1;
	return (result);
}

int	append_to_token(char **current_token, char c)
{
	char	*temp;
	int		len;

	len = ft_strlen(*current_token);
	temp = (char *)malloc(len + 2);
	if (!temp)
		return (0);
	ft_strcpy(temp, *current_token);
	temp[len] = c;
	temp[len + 1] = '\0';
	free(*current_token);
	*current_token = temp;
	return (1);
}

int	is_special(char *quoted_part)
{
	if (!ft_strncmp(quoted_part, "<", INT_MAX))
		return (1);
	if (!ft_strncmp(quoted_part, "<<", INT_MAX))
		return (1);
	if (!ft_strncmp(quoted_part, ">", INT_MAX))
		return (1);
	if (!ft_strncmp(quoted_part, ">>", INT_MAX))
		return (1);
	if (!ft_strncmp(quoted_part, "|", INT_MAX))
		return (1);
	return (0);
}

void	handle_special_char(t_node **head, t_mini *t, char *input, int *i)
{
	char	special[3];

	special[0] = '\0';
	special[1] = '\0';
	special[2] = '\0';
	special[0] = input[*i];
	if ((input[*i] == '>' || input[*i] == '<') && input[*i + 1] == input[*i])
	{
		special[1] = input[*i];
		(*i)++;
	}
	add_token(head, create_token(special, get_token_type(special, t)));
	(*i)++;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:54:25 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/17 08:34:12 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_status(char *expanded, int *j, int last_exit_status)
{
	char	*exit_str;
	int		len;

	exit_str = ft_itoa(last_exit_status);
	if (!exit_str)
		return (expanded);
	len = ft_strlen(exit_str);
	ft_strcpy(expanded + *j, exit_str);
	*j += len;
	free(exit_str);
	return (expanded);
}

char	*expand_env_variable(char *str, int *i, char *expanded, int *j)
{
	char	*var_name;
	char	*env_value;

	var_name = ft_substr(str, *i, ft_varlen(str + *i));
	env_value = getenv(var_name);
	free(var_name);
	if (env_value)
	{
		ft_strcpy(expanded + *j, env_value);
		*j += ft_strlen(env_value);
	}
	*i += ft_varlen(str + *i);
	return (expanded);
}

char	*process_dollar_sign(char *str, int *i, char *expanded, int *j, int last_exit_status)
{
	(*i)++;
	if (str[*i] == '?')
	{
		expanded = expand_exit_status(expanded, j, last_exit_status);
		(*i)++;
	}
	else
		expanded = expand_env_variable(str, i, expanded, j);
	return (expanded);
}

char	*expand_variables(char *str, int last_exit_status)
{
	char	*expanded;
	int		i;
	int		j;

	i = 0;
	j = 0;
	expanded = malloc(1024);
	if (!expanded)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
			expanded = process_dollar_sign(str, &i, expanded, &j, last_exit_status);
		else
			expanded[j++] = str[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}

int	ft_varlen(char *str)
{
	int	len = 0;

	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}


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

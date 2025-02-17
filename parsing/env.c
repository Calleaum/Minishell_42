/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:54:45 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/17 18:30:20 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	get_var_size(char *str, int *i)
{
	char	*var_name;
	char	*env_value;
	size_t	size;

	size = 0;
	var_name = ft_substr(str, *i, ft_varlen(str + *i));
	if (var_name)
	{
		env_value = getenv(var_name);
		if (env_value)
			size = ft_strlen(env_value);
		free(var_name);
		*i += ft_varlen(str + *i);
	}
	return (size);
}

size_t	handle_dollar(char *str, int *i, int last_exit_status)
{
	size_t	size;
	char	*exit_str;

	size = 0;
	(*i)++;
	if (str[*i] == '?')
	{
		exit_str = ft_itoa(last_exit_status);
		if (exit_str)
			size += ft_strlen(exit_str);
		free(exit_str);
		(*i)++;
	}
	else
		size += get_var_size(str, i);
	return (size);
}

char	*expand_env_variable(char *str, int *i, t_expand *exp)
{
	char	*var_name;
	char	*env_value;

	var_name = ft_substr(str, *i, ft_varlen(str + *i));
	if (!var_name)
		return (exp->expanded);
	env_value = getenv(var_name);
	if (env_value)
	{
		ft_strcpy(exp->expanded + exp->j, env_value);
		exp->j += ft_strlen(env_value);
	}
	free(var_name);
	*i += ft_varlen(str + *i);
	return (exp->expanded);
}

static char	*process_dollar_sign(char *str, int *i, t_expand *exp,
		int last_exit_status)
{
	(*i)++;
	if (str[*i] == '?')
	{
		exp->expanded = expand_exit_status(exp, last_exit_status);
		(*i)++;
	}
	else
		exp->expanded = expand_env_variable(str, i, exp);
	return (exp->expanded);
}

char	*expand_variables(char *str, int last_exit_status)
{
	t_expand	exp;
	int			i;

	if (!str)
		return (NULL);
	exp.expanded = malloc(calculate_expanded_size(str, last_exit_status));
	if (!exp.expanded)
		return (NULL);
	i = 0;
	exp.j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			exp.expanded = process_dollar_sign(str, &i, &exp, last_exit_status);
		else
			exp.expanded[exp.j++] = str[i++];
	}
	exp.expanded[exp.j] = '\0';
	return (exp.expanded);
}

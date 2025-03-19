/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:35:30 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/04 10:35:58 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	handle_exit_status(int *i, int last_exit_status)
{
	size_t	size;
	char	*exit_str;

	size = 0;
	exit_str = ft_itoa(last_exit_status);
	if (exit_str)
	{
		size = ft_strlen(exit_str);
		free(exit_str);
	}
	(*i)++;
	return (size);
}

static size_t	handle_env_variable(char *str, int *i, t_env *env)
{
	size_t	size;
	char	*var_name;
	char	*env_value;

	size = 0;
	var_name = ft_substr(str, *i, ft_varlen(str + *i));
	if (var_name)
	{
		env_value = get_env_value(env, var_name);
		if (env_value)
			size = ft_strlen(env_value);
		free(var_name);
		*i += ft_varlen(str + *i);
	}
	return (size);
}

size_t	handle_dollar(char *str, int *i, int last_exit_status, t_env *env)
{
	size_t	size;

	size = 0;
	(*i)++;
	if (str[*i] == '?')
		size = handle_exit_status(i, last_exit_status);
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
		size = handle_env_variable(str, i, env);
	else
		size = 1;
	return (size);
}

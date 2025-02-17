/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:54:45 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/17 11:04:44 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

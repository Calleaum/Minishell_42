/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:54:45 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/17 14:13:48 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_exit_status(t_expand *exp, int last_exit_status)
{
	char	*exit_str;
	int		len;

	exit_str = ft_itoa(last_exit_status);
	if (!exit_str)
		return (exp->expanded);
	len = ft_strlen(exit_str);
	ft_strcpy(exp->expanded + exp->j, exit_str);
	exp->j += len;
	free(exit_str);
	return (exp->expanded);
}

char	*expand_env_variable(char *str, int *i, t_expand *exp)
{
	char	*var_name;
	char	*env_value;

	var_name = ft_substr(str, *i, ft_varlen(str + *i));
	env_value = getenv(var_name);
	free(var_name);
	if (env_value)
	{
		ft_strcpy(exp->expanded + exp->j, env_value);
		exp->j += ft_strlen(env_value);
	}
	*i += ft_varlen(str + *i);
	return (exp->expanded);
}

char	*process_dollar_sign(char *str, int *i, t_expand *exp,
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

	i = 0;
	exp.j = 0;
	exp.expanded = malloc(1024);
	if (!exp.expanded)
		return (NULL);
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

int	ft_varlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

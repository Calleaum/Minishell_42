/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:54:45 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/24 14:01:14 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;

	env = malloc(sizeof(t_env));
	if (!(env))
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	env->count = i;
	env->env_vars = malloc(sizeof(char *) * (i + 1));
	if (!(env->env_vars))
		return (free(env), NULL);
	i = 0;
	while (envp[i])
	{
		env->env_vars[i] = ft_strdup(envp[i]);
		if (!(env->env_vars[i]))
			return (free_env(env), NULL);
		i++;
	}
	env->last_exit_status = 0;
	env->env_vars[i] = NULL;
	env->tokens = NULL;
	return (env);
}

char	*get_env_value(t_env *env, const char *name)
{
	int		i;
	size_t	name_len;
	char	*env_var;
	char	*equals_sign;

	if (!env || !name || !env->env_vars)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (i < env->count && env->env_vars[i])
	{
		env_var = env->env_vars[i];
		equals_sign = ft_strchr(env_var, '=');
		if (equals_sign
			&& (size_t)(equals_sign - env_var) == name_len
			&& ft_strncmp(env_var, name, name_len) == 0)
			return (equals_sign + 1);
		i++;
	}
	return (NULL);
}

int	set_env_value(t_env *env, const char *name, const char *value)
{
	int		i;
	char	*new_var;

	if (!env || !name)
		return (0);
	i = 0;
	while (env->env_vars[i])
	{
		if (ft_strncmp(env->env_vars[i], name, ft_strlen(name)) == 0
			&& env->env_vars[i][ft_strlen(name)] == '=')
		{
			free(env->env_vars[i]);
			new_var = ft_strjoin3(name, "=", value);
			if (!new_var)
				return (0);
			env->env_vars[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

char	*expand_env_variable(char *str, int *i, t_expand *exp, t_env *env)
{
	char	*var_name;
	char	*env_value;

	var_name = ft_substr(str, *i, ft_varlen(str + *i));
	if (!var_name)
		return (exp->expanded);
	env_value = get_env_value(env, var_name);
	if (env_value)
	{
		ft_strcpy(exp->expanded + exp->j, env_value);
		exp->j += ft_strlen(env_value);
	}
	free(var_name);
	*i += ft_varlen(str + *i);
	return (exp->expanded);
}

char	*process_dollar_sign(char *str, t_expand *exp, t_env *env, int hd)
{
	char	*var_name;

	exp->i++;
	if (str[exp->i] == '?' && !exp->sq)
	{
		if (!expand_exit_status(exp, env->last_exit_status))
			return (NULL);
		exp->i++;
	}
	else if ((ft_isalpha(str[exp->i]) || str[exp->i] == '_') && !exp->sq)
	{
		var_name = ft_substr(str, exp->i, ft_varlen(str + exp->i));
		free(var_name);
		if (!expand_env_variable(str, &exp->i, exp, env))
			return (NULL);
	}
	else if ((!((str[exp->i] == '\'' || str[exp->i] == '"')
				&& !exp->sq && !exp->dq) || !str[exp->i]) || hd)
		exp->expanded[exp->j++] = '$';
	return (exp->expanded);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:11:58 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/31 15:05:57 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*extract_var_name(const char *var, char *equals)
{
	char	*var_name;
	int		name_len;

	if (equals)
		name_len = equals - var;
	else
		name_len = ft_strlen(var);
	var_name = malloc(name_len + 1);
	if (!var_name)
		return (NULL);
	str_n_copy(var_name, var, name_len);
	var_name[name_len] = '\0';
	return (var_name);
}

static int	replace_existing_var(t_env *env, int index, const char *var)
{
	char	*new_var;

	new_var = ft_strdup(var);
	if (!new_var)
		return (0);
	free(env->env_vars[index]);
	env->env_vars[index] = new_var;
	return (1);
}

static int	find_env_var_index(t_env *env, const char *var_name)
{
	int		i;
	char	*env_equals;
	char	*env_name;

	i = 0;
	while (i < env->count)
	{
		env_equals = ft_strchr(env->env_vars[i], '=');
		if (env_equals)
		{
			env_name = extract_var_name(env->env_vars[i], env_equals);
			if (!env_name)
				return (-1);
			if (ft_conststrcmp(env_name, var_name) == 0)
				return (free(env_name), i);
			free(env_name);
		}
		else if (ft_conststrcmp(env->env_vars[i], var_name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	add_new_env_var(t_env *env, const char *var)
{
	char	**new_env_vars;
	int		i;

	new_env_vars = malloc(sizeof(char *) * (env->count + 2));
	if (!new_env_vars)
		return (0);
	i = 0;
	while (i < env->count)
	{
		new_env_vars[i] = env->env_vars[i];
		i++;
	}
	new_env_vars[i] = ft_strdup(var);
	if (!new_env_vars[i])
		return (free(new_env_vars), 0);
	new_env_vars[i + 1] = NULL;
	free(env->env_vars);
	env->env_vars = new_env_vars;
	env->count++;
	return (1);
}

int	update_or_add_env_var(t_env *env, const char *var)
{
	char	*equals;
	char	*var_name;
	int		index;

	equals = ft_strchr(var, '=');
	var_name = extract_var_name(var, equals);
	if (!var_name)
		return (0);
	index = find_env_var_index(env, var_name);
	if (index >= 0)
	{
		free(var_name);
		return (replace_existing_var(env, index, var));
	}
	free(var_name);
	return (add_new_env_var(env, var));
}

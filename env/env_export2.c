/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:32:40 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/24 11:54:05 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_new_var(char **new_var, char *arg, int name_len, char *equals)
{
	int	total_len;

	total_len = name_len + ft_strlen(equals) + 1;
	*new_var = malloc(total_len);
	if (!(*new_var))
		return (0);
	str_n_copy(*new_var, arg, name_len);
	ft_strcpy(*new_var + name_len, equals);
	return (1);
}

int	init_export_var(char *arg, char *var_name, int *name_len, t_mini *mini)
{
	char		*equals;
	int			var_name_size;

	var_name_size = 256;
	equals = ft_strchr(arg, '=');
	if (equals != NULL)
		*name_len = equals - arg;
	else
		*name_len = ft_strlen(arg);
	if (*name_len >= var_name_size - 1)
		*name_len = var_name_size - 1;
	ft_memset(var_name, 0, var_name_size);
	if (!validate_var_name(arg, *name_len))
	{
		fd_printf(2, "export: '%s': not a valid identifier\n", arg);
		return (mini->last_exit_status = 1, 1);
	}
	str_n_copy(var_name, arg, *name_len);
	var_name[*name_len] = '\0';
	return (1);
}

int	handle_export_arg(t_mini *mini, char *arg)
{
	char	var_name[256];
	char	*equals;
	char	*new_var;
	int		name_len;

	if (!init_export_var(arg, var_name, &name_len, mini))
		return (mini->last_exit_status = 127, 0);
	equals = ft_strchr(arg, '=');
	if (equals == NULL)
	{
		if (!var_exists(mini->env, var_name))
		{
			if (!add_env_var_no_value(mini->env, var_name))
				return (mini->last_exit_status = 1, 0);
		}
		return (mini->last_exit_status = 0, 1);
	}
	if (!create_new_var(&new_var, arg, name_len, equals))
		return (mini->last_exit_status = 1, 0);
	if (!update_or_add_env_var(mini->env, new_var))
		return (free(new_var), mini->last_exit_status = 1, 0);
	free(new_var);
	mini->last_exit_status = 0;
	return (1);
}

int	add_env_var_no_value(t_env *env, const char *name)
{
	char	**new_env_vars;
	char	*new_var;
	int		i;

	new_env_vars = malloc(sizeof(char *) * (env->count + 2));
	if (!new_env_vars)
		return (0);
	i = -1;
	while (++i < env->count)
		new_env_vars[i] = env->env_vars[i];
	new_var = ft_strdup(name);
	if (!new_var)
	{
		free(new_env_vars);
		return (0);
	}
	new_env_vars[env->count] = new_var;
	new_env_vars[env->count + 1] = NULL;
	free(env->env_vars);
	env->env_vars = new_env_vars;
	env->count++;
	return (1);
}

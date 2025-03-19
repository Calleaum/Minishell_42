/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:28:51 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/17 17:14:08 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	replace_env_var(t_env *env, const char *name, const char *value)
{
	char	*new_var;
	int		i;

	i = 0;
	while (i < env->count)
	{
		if (env->env_vars[i]
			&& ft_strncmp(env->env_vars[i], name, ft_strlen(name)) == 0
			&& (env->env_vars[i][ft_strlen(name)] == '='
			|| env->env_vars[i][ft_strlen(name)] == '\0'))
		{
			free(env->env_vars[i]);
			if (value == NULL || value[0] == '\0')
				new_var = ft_strdup(name);
			else
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

static int	add_new_env_var(t_env *env, const char *name, const char *value)
{
	char	**new_env_vars;
	char	*new_var;
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
	if (value == NULL || value[0] == '\0')
		new_var = ft_strdup(name);
	else
		new_var = ft_strjoin3(name, "=", value);
	if (!new_var)
		return (free(new_env_vars), 0);
	new_env_vars[env->count] = new_var;
	new_env_vars[env->count + 1] = NULL;
	free(env->env_vars);
	env->env_vars = new_env_vars;
	env->count++;
	return (1);
}

int	add_env_value(t_env *env, const char *name, const char *value)
{
	if (!env || !name)
		return (0);
	if (replace_env_var(env, name, value))
		return (1);
	return (add_new_env_var(env, name, value));
}

int	init_shell_vars(t_env *env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (!get_env_value(env, "PWD"))
			add_env_value(env, "PWD", cwd);
	}
	if (!get_env_value(env, "PATH"))
		add_env_value(env, "PATH",
			"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (!get_env_value(env, "OLDPWD"))
		add_env_value(env, "OLDPWD", "");
	return (1);
}

int	update_pwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	old_pwd = get_env_value(env, "PWD");
	if (old_pwd)
	{
		if (get_env_value(env, "OLDPWD"))
			set_env_value(env, "OLDPWD", old_pwd);
		else
			add_env_value(env, "OLDPWD", old_pwd);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (0);
	if (get_env_value(env, "PWD"))
		return (set_env_value(env, "PWD", cwd));
	else
		return (add_env_value(env, "PWD", cwd));
}

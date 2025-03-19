/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:05:21 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/17 17:07:32 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*handle_home_path(t_mini *mini, int *error)
{
	char	*path;

	path = get_env_value(mini->env, "HOME");
	if (!path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		*error = 1;
		return (NULL);
	}
	return (path);
}

static char	*get_special_path(t_mini *mini, int *error, char *special)
{
	char	*path;
	char	*msg;

	if (ft_strcmp(special, "~") == 0)
		msg = "HOME";
	else
		msg = "OLDPWD";
	path = get_env_value(mini->env, msg);
	if (!path || (ft_strcmp(special, "-") == 0 && !*path))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(" not set\n", 2);
		*error = 1;
		return (NULL);
	}
	if (ft_strcmp(special, "-") == 0)
		ft_putendl_fd(path, 1);
	return (path);
}

static char	*handle_arg_path(t_mini *mini, int *error, t_node *arg_node)
{
	char	*path;

	if (ft_strcmp(arg_node->data, "~") == 0
		|| ft_strcmp(arg_node->data, "-") == 0)
	{
		path = get_special_path(mini, error, arg_node->data);
		if (*error)
			return (NULL);
	}
	else if (arg_node->next)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		*error = 1;
		return (NULL);
	}
	else
		path = arg_node->data;
	return (path);
}

static char	*get_target_path(t_mini *mini, int *error, t_node *tokens)
{
	t_node	*arg_node;

	*error = 0;
	arg_node = tokens->next;
	if (!arg_node)
		return (handle_home_path(mini, error));
	return (handle_arg_path(mini, error, arg_node));
}

int	ft_cd(t_mini *mini, t_node *list)
{
	char	*path;
	int		error;

	error = 0;
	path = get_target_path(mini, &error, list);
	if (error)
	{
		mini->last_exit_status = 1;
		return (1);
	}
	if (chdir(path) != 0)
	{
		mini->last_exit_status = handle_cd_error(path);
		return (1);
	}
	update_pwd(mini->env);
	mini->last_exit_status = 0;
	return (0);
}

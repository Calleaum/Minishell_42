/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:44:20 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/20 12:22:35 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	remove_env_var(t_env *env, const char *var_name)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < (size_t)env->count)
	{
		if (check_env_match(env->env_vars[i], var_name))
		{
			free(env->env_vars[i]);
			j = i;
			while (++j < (size_t)env->count)
				env->env_vars[j - 1] = env->env_vars[j];
			env->env_vars[--env->count] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

static int is_valid_identifier(const char *name)
{
	int i;
	
	if (!name || !*name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	
	return (1);
}

static int	remove_env_var_from_tokens(t_node **head, const char *var_name)
{
	t_node	*current;
	t_node	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (check_token_match(current->data, var_name))
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->data);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

/* Traiter l'argument unset */
static int handle_unset_arg(t_env *env, char *arg)
{
	char var_name[256];
	size_t name_len;
	int result_env_var;
	int result_list;
	
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	name_len = ft_strlen(arg);
	if (name_len >= (size_t)(sizeof(var_name) - 1))
		name_len = sizeof(var_name) - 1;
	ft_memset(var_name, 0, sizeof(var_name));
	str_n_copy(var_name, arg, name_len);
	var_name[name_len] = '\0';
	
	result_env_var = remove_env_var(env, var_name);
	result_list = remove_env_var_from_tokens(&env->tokens, var_name);
	
	return (result_env_var || result_list);
}


/* Fonction principale pour unset */
int ft_unset(t_env *env, t_node *list, t_mini *mini)
{
	t_node *current;
	int success;
	int error_found;
	
	success = 1;
	error_found = 0;
	current = list->next;
	
	while (current != NULL)
	{
		if (!handle_unset_arg(env, current->data))
		{
			error_found = 1;
		}
		current = current->next;
	}
	mini->last_exit_status = error_found ? 1 : 0;
	return (success);
}

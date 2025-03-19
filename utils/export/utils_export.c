/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:00:02 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/18 12:13:59 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*str_n_copy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_valid_first_char(char c)
{
	return (c == '_'
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}

int	is_valid_subsequent_char(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| (c == '_'));
}

int	validate_var_name(char *arg, int name_len)
{
	int	j;

	j = 1;
	if (*arg == '\0')
		return (0);
	if (!is_valid_first_char(*arg))
		return (0);
	while (j < name_len)
	{
		if (!is_valid_subsequent_char(arg[j]))
			return (0);
		j++;
	}
	return (1);
}

int	var_exists(t_env *env, char *arg)
{
	int		k;
	char	*check_var;
	char	*equals;
	int		exists;

	k = 0;
	exists = 0;
	while (k < env->count)
	{
		check_var = env->env_vars[k];
		equals = strchr(check_var, '=');
		if (equals)
		{
			*equals = '\0';
			exists = (ft_strcmp(check_var, arg) == 0);
			*equals = '=';
		}
		else
			exists = (ft_strcmp(check_var, arg) == 0);
		if (exists)
			return (1);
		k++;
	}
	return (0);
}

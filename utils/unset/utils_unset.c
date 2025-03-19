/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:30:11 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/18 12:14:55 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_env_match(char *env_var, const char *var_name)
{
	char	*equals;
	size_t	len;

	equals = ft_strchr(env_var, '=');
	len = 0;
	if (equals != NULL)
		len = (size_t)(equals - env_var);
	else
		len = ft_strlen(env_var);
	return (ft_strncmp(env_var, var_name, len) == 0 && var_name[len] == '\0');
}

int	check_token_match(char *token_data, const char *var_name)
{
	char	*equals;
	size_t	len;

	equals = ft_strchr(token_data, '=');
	if (equals)
		len = (size_t)(equals - token_data);
	else
		len = ft_strlen(token_data);
	return (ft_strncmp(token_data, var_name, len) == 0
		&& var_name[len] == '\0');
}

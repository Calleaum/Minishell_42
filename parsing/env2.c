/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:16:06 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/17 18:29:38 by calleaum         ###   ########.fr       */
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

size_t	calculate_expanded_size(char *str, int last_exit_status)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			size += handle_dollar(str, &i, last_exit_status);
		else
		{
			size++;
			i++;
		}
	}
	return (size + 1);
}

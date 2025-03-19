/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:16:06 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/17 17:20:17 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_exp(t_expand *exp)
{
	exp->i = 0;
	exp->j = 0;
	exp->sq = 0;
	exp->dq = 0;
	exp->in_quote = 0;
}

char	*expand_variables(char *str, int lst_ex_stat, t_env *env)
{
	t_expand		exp;

	if (!str)
		return (NULL);
	env->last_exit_status = lst_ex_stat;
	exp.expanded = ft_calloc(calc_exp_siz(str, lst_ex_stat, env), sizeof(char));
	if (!exp.expanded)
		return (NULL);
	init_exp(&exp);
	while (str[exp.i])
	{
		if (str[exp.i] == '\'' || str[exp.i] == '"')
		{
			if (str[exp.i] == '\'' && !exp.dq)
				exp.sq = !exp.sq;
			if (str[exp.i] == '"' && !exp.sq)
				exp.dq = !exp.dq;
		}
		if (str[exp.i] == '$')
			exp.expanded = process_dollar_sign(str, &exp.i, &exp, env);
		else
			exp.expanded[exp.j++] = str[exp.i++];
	}
	exp.expanded[exp.j] = '\0';
	return (exp.expanded);
}

char	*expand_exit_status(t_expand *exp, int last_exit_status)
{
	char	*exit_str;
	int		len;

	if (exp->expanded[exp->j] == '?' && exp->j > 0
		&& exp->expanded[exp->j - 1] == '$')
	{
		fd_printf(2, "%d", last_exit_status);
		exp->j++;
		return (exp->expanded);
	}
	exit_str = ft_itoa(last_exit_status);
	if (!exit_str)
		return (exp->expanded);
	len = ft_strlen(exit_str);
	ft_strcpy(exp->expanded + exp->j, exit_str);
	exp->j += len;
	free(exit_str);
	return (exp->expanded);
}

// Fonction modifiée calculate_expanded_size
size_t	calc_exp_siz(char *str, int last_exit_status, t_env *env)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			size += handle_dollar(str, &i, last_exit_status, env);
		else
		{
			size++;
			i++;
		}
	}
	return (size + 1);
}

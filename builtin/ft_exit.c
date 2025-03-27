/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:06:09 by lgrisel           #+#    #+#             */
/*   Updated: 2025/03/27 17:33:49 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long long	ft_atoll(const char *str, long long *j)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (sign == -1 && ft_strncmp(str, "9223372036854775808", 19) == 0
		&& (str[19] == '\0' || (str[19] >= '0' && str[19] <= '9')))
		return (LLONG_MIN);
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LLONG_MAX - (*str - '0')) / 10)
			return ((*j) = 1, 0);
		result = result * 10 + (*str++ - '0');
	}
	return (result * sign);
}

void	ft_exit(t_node *list)
{
	long long	i;
	long long	j;

	j = 0;
	if (list->next && list->next->next && isdigit_str(list->next->data))
	{
		ft_putendl_fd("exit\nminishell: exit: too many arguments", 2);
		// free_listenv(mini, list);
		free_list(list);
		exit(1);
	}
	if (list->next)
		i = ft_atoll(list->next->data, &j);
	else
		i = 0;
	if ((list->next && !isdigit_str(list->next->data)) || !j == 0)
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(list->next->data, 2);
		ft_putendl_fd(": numeric argument required", 2);
		// free_listenv(mini, list);
		free_list(list);
		exit(2);
	}
	// free_listenv(mini, list);
	free_list(list);
	ft_putendl_fd("exit", 2);
	exit(i);
}

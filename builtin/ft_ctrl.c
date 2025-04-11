/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:34:05 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/11 11:21:38 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// 🖕
static void	sig_handler_interactive(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 130;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	sig_handler_interactive2(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 130;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		close(0);
	}
}

static void	sig_handler_interactive3(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 131;
		rl_replace_line("", 0);
	}
}

void	set_sig_interactive(int i)
{
	signal(SIGQUIT, SIG_IGN);
	if (i == 0)
		signal(SIGINT, sig_handler_interactive);
	else if (i == 1)
		signal(SIGINT, SIG_IGN);
	else if (i == 2)
		signal(SIGINT, sig_handler_interactive3);
}

void	set_sig_executing(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_interactive2);
}

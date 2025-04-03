/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:34:05 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/03 14:45:50 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// 🖕
static void sig_handler_interactive(int signal)
{
	// 	fd_printf(2, "sig: %d", g_signal);
	// if (g_signal == -1)
	// 	fd_printf(2, "oui\n");
	if (signal == SIGINT && g_signal != -1)
	{
		g_signal = 130;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void sig_handler_executing(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	else if (signal == SIGINT)
	{
		g_signal = -1;
		close(0);
	}
	else
		g_signal = signal;
}

void set_sig_interactive(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_interactive);
}

void set_sig_executing(void)
{
	signal(SIGQUIT, sig_handler_executing);
	signal(SIGINT, sig_handler_executing);
}

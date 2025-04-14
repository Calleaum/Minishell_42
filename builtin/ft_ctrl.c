/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:34:05 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/14 13:21:17 by lgrisel          ###   ########.fr       */
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

static void	sig_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 130;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		close(0);
	}
}

static void	sig_handler_catas(int signal)
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
		signal(SIGINT, sig_handler_catas);
}

void	set_sig_executing(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_heredoc);
}

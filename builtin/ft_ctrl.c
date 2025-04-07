/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:34:05 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/07 12:53:49 by lgrisel          ###   ########.fr       */
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
	}
}

static void	sig_handler_executing(int signal)
{
	if (signal == SIGQUIT)
		return ;
	else if (signal == SIGINT)
	{
		g_signal = -1;
		close(0);
	}
	else
		g_signal = signal;
}

void	set_sig_interactive(int i)
{
	// struct termios	term;

	// if (tcgetattr(STDIN_FILENO, &term) == 0)
	// {
	// 	term.c_lflag |= ECHOCTL;
	// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// }
	signal(SIGQUIT, SIG_IGN);
	if (i == 0)
		signal(SIGINT, sig_handler_interactive);
	else
		signal(SIGINT, sig_handler_interactive2);
}

void	set_sig_executing(void)
{
	// struct termios	term;

	// if (tcgetattr(STDIN_FILENO, &term) == 0)
	// {
	// 	term.c_lflag &= ~ECHOCTL;
	// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// }
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_executing);
}

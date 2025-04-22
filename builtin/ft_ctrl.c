/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:34:05 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/22 17:50:42 by lgrisel          ###   ########.fr       */
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

void	sig_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 130;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		close (0);
	}
}

static void	sig_handler_catas(int signal)
{
	if (signal == SIGQUIT)
		g_signal = 131;
	if (signal == SIGINT)
	{
		g_signal = 132;
		rl_replace_line("", 0);
	}
}

void	set_sig_interactive(int i)
{
	if (i != 2)
		signal(SIGQUIT, SIG_IGN);
	if (i == 0)
		signal(SIGINT, sig_handler_interactive);
	else if (i == 1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
	else if (i == 2)
	{
		signal(SIGINT, sig_handler_catas);
		signal(SIGQUIT, sig_handler_catas);
	}
}

// void	set_sig_executing(void)
// {
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, sig_handler_heredoc);
// }




// in my minishell when i enter in a heredoc and i exit it with ctrl+C here is what i get
// minishell$ << a
// > ^C

// minishell$ 

// so everything is good exept the empty line before the second prompt how can i fix it here is my signal function for it
// static void	sig_handler_heredoc(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		g_signal = 130;
// 		rl_replace_line("", 0);
// 		write(STDOUT_FILENO, "\n", 1);
// 	}
// }

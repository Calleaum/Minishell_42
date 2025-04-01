/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:34:05 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/31 09:38:50 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void sig_handler_interactive(int signal) 
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


static void sig_handler_executing(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	else if (signal == SIGINT)
	{
		g_signal = 130;
		// ft_putstr_fd("\n", STDOUT_FILENO);
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

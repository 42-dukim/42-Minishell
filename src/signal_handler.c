/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:04:53 by junkwak           #+#    #+#             */
/*   Updated: 2025/01/07 21:41:15 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	sigint_handler(int signum)
{
	g_signal = signum;
	if (signum != SIGINT)
		return ;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_all_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_all_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_terminal(t_bool c_lflag)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (c_lflag)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	enroll_custom_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

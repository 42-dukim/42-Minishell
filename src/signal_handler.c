/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:04:53 by junkwak           #+#    #+#             */
/*   Updated: 2025/01/07 17:34:08 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	disable_ctrl_backslash(void)
{
	struct termios	term; 

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	sig_int_execve(int signo)
{
	g_signal = signo;
	write(1, "\n", 1);
	rl_redisplay();
}

void	sig_quit_execve(int signo)
{
	g_signal = signo;
	disable_ctrl_backslash();
	write(1, "Quit (core dumped)\n", 19);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigint_handler(int signum)//prompt
{
	g_signal = signum;
	if (signum != SIGINT)
		return ;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigquit_handler(int signum)
{
	(void)signum;
	disable_ctrl_backslash();
	rl_on_new_line();
	rl_redisplay();
}

void	enroll_custom_signal(void)//현재프로세스터미널표시(시그널기본상태)
{
	disable_ctrl_backslash();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
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

void	signal_handle_execve(void)
{
	signal(SIGINT, sig_int_execve);
	signal(SIGQUIT, sig_quit_execve);
}

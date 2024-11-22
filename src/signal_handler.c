/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:30:16 by dukim             #+#    #+#             */
/*   Updated: 2024/11/22 22:30:17 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	sigint_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("minishell$ \n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigquit_handler(int signum)
{
	(void)signum;
}

static void	disable_ctrl_backslash(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	enroll_custom_signal(void)
{
	disable_ctrl_backslash();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

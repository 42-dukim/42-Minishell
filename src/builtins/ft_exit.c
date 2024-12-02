/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:48:18 by dukim             #+#    #+#             */
/*   Updated: 2024/11/29 21:48:19 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_global	g_data;

void	ft_exit(void)
{
	rl_clear_history();
	ft_freesplit(g_data.envp);
	ft_freesplit(g_data.path_list);
	printf("exit\n");
	exit(0);
}

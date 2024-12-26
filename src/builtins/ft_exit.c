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

void	ft_exit(t_envval *env_val)
{
	rl_clear_history();
	ft_lstclear(&(env_val->lst), free_env);
	ft_freesplit(env_val->paths);
	printf("exit\n");
	exit(0);
}

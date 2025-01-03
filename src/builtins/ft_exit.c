/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:48:18 by dukim             #+#    #+#             */
/*   Updated: 2025/01/03 16:40:22 by junkwak          ###   ########.fr       */
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

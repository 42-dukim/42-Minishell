/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:12:12 by dukim             #+#    #+#             */
/*   Updated: 2024/12/13 17:48:56 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_global	g_data;

void	ft_env(char **cmds)
{
	size_t	i;

	i = 0;
	if (cmds[++i])//env 이후 추가명령어 나오면 무조건 에러출력
	{
		printf("env : '%s' : No such file or directory\n",cmds[i]);
		return ;
	}
	while (g_data.envp[i])
	{
		printf("%s\n", g_data.envp[i]);
		i++;
	}
}

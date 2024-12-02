/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:57:02 by dukim             #+#    #+#             */
/*   Updated: 2024/11/23 00:57:03 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_global	g_data;

int	builtin_handler(char **cmds, char **env_list)
{
	const char	*cmd;

	cmd = cmds[0];
	if (ft_strncmp(cmd, "cd", 2) == 0)
	{
		ft_cd(cmds[1], ft_getenv(g_data.envp, "HOME"));
		return (1);
	}
	if (ft_strncmp(cmd, "exit", 4) == 0)
		ft_exit();
	if (ft_strncmp(cmd, "env", 3) == 0)
	{
		ft_env();
		return (1);
	}
	return (0);
}

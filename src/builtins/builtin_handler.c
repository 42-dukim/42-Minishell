/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:57:02 by dukim             #+#    #+#             */
/*   Updated: 2024/12/13 17:53:01 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_global	g_data;

int	builtin_handler(char **cmds)
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
		ft_env(cmds);
		return (1);
	}
	if (ft_strncmp(cmd, "export", 6) == 0)
	{
		ft_export(cmds);
		return (1);
	}
	return (0);
}

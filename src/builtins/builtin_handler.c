/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:57:02 by dukim             #+#    #+#             */
/*   Updated: 2024/12/17 16:51:20 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../command/command.h"

extern t_global	g_data;

int	builtin_handler(void *ptr)
{
	t_command	*cmd;

	cmd = (t_command *)ptr;
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		ft_cd(cmd->args[1], ft_getenv("HOME"));
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		ft_exit();
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		ft_env(cmd->args);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		ft_export(cmd->args);
	else
		return (0);
	return (1);
}

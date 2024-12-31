/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:57:02 by dukim             #+#    #+#             */
/*   Updated: 2024/12/26 14:01:10 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../command/command.h"

t_bool	is_builtin_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0 || \
		ft_strncmp(cmd, "exit", 5) == 0 || \
		ft_strncmp(cmd, "env", 4) == 0 || \
		ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	return (false);
}

void	builtin_handler(void *ptr, t_envval *env_val)
{
	t_command	*cmd;
	int			fd[2];

	cmd = (t_command *)ptr;
	if (redirect_io(cmd->redi, fd))
	{
		if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
			ft_cd(cmd->args[1], env_val->lst);
		else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
			ft_exit(env_val);
		else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
			ft_env(cmd->args, env_val->lst);
		else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
			ft_export(cmd->args, env_val);
	}
	unredirect_io(fd);
}

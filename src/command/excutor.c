/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:12:06 by dukim             #+#    #+#             */
/*   Updated: 2024/12/24 19:12:08 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static void	execute_command(t_command *cmd, t_envval *env_val)
{
	char	*cmd_path;

	if (!builtin_handler(cmd, env_val))
	{
		cmd_path = get_cmd_abspath(cmd->args[0], env_val->paths);
		if (cmd_path)
		{
			if (fork() == 0)
			{
				redirect_io(cmd->redi);
				// execve(cmd_path, cmd->args, env_val->lst);	// list to char **
			}
			wait(NULL);
		}
		else
			printf("%s: command not found\n", cmd->args[0]);
		free(cmd_path);
	}
}

void	execute_commands(t_list *cmd_list, t_envval *env_val)
{
	pid_t	*pids;
	size_t	len;
	size_t	i;

	len = ft_lstsize(cmd_list);
	i = 0;
	if (len == 1)
	{
		execute_command(((t_cmd_unit *)cmd_list->content)->cmd, env_val);
		return ;
	}
	pids = malloc(sizeof(pid_t) * len);
	while (cmd_list)
	{
		if (((t_cmd_unit *)cmd_list->content)->type == CMD)
		{
			pids[i] = fork();
			if (pids[i++] == 0)
			{
				execute_command(((t_cmd_unit *)cmd_list->content)->cmd, env_val);
				exit(1);
			}
		}
		cmd_list = cmd_list->next;
	}
	i = 0;
	while (i < len)
		waitpid(pids[i++], NULL, 0);
	free(pids);
}

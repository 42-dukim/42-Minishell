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

extern t_global	g_data;

static void	redirect_io(t_redirection *redi)
{
	int	fd;

	while (redi)
	{
		if (redi->type == '>')
		{
			fd = open(redi->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
		}
		if (redi->type == '<')
		{
			fd = open(redi->file, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		// TODO: >>, <<
		close(fd);
		redi = redi->next;
	}
}

static void	execute_command(t_command *cmd, t_list *env_list)
{
	char	*cmd_path;

	if (!builtin_handler(cmd->args))
	{
		cmd_path = get_cmd_abspath(cmd->args[0], env_list);
		if (cmd_path)
		{
			if (fork() == 0)
			{
				redirect_io(cmd->redi);
				execve(cmd_path, cmd->args, g_data.envp);
			}
			wait(NULL);
		}
		else	
			printf("%s: command not found\n", cmd->args[0]);
		free(cmd_path);
	}
}

void	execute_commands(t_list *cmd_list)
{
	pid_t	*pids;
	size_t	len;
	size_t	i;

	len = ft_lstsize(cmd_list);
	i = 0;
	if (len == 1)
	{
		execute_command(((t_cmd_unit *)cmd_list->content)->cmd, NULL);
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
				execute_command(((t_cmd_unit *)cmd_list->content)->cmd, NULL);
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
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

static void	convert_lst_toenvp(t_envval *env_val)
{
	size_t	i;
	char	*temp;
	t_list	*ptr;

	if (!env_val->is_changed)
		return ;
	ft_freesplit(env_val->envp);
	env_val->envp = malloc(sizeof(char *) * (ft_lstsize(env_val->lst) + 1));
	i = 0;
	ptr = env_val->lst;
	while (ptr)
	{
		temp = ft_strjoin(((t_env *)ptr->content)->key, "=");
		env_val->envp[i++] = ft_strjoin(temp, ((t_env *)ptr->content)->value);
		free(temp);
		ptr = ptr->next;
	}
	env_val->envp[i] = NULL;
	env_val->is_changed = false;
}

static void	execute_command(t_command *cmd, t_envval *env_val)
{
	char	*cmd_path;

	if (is_builtin_cmd(cmd->args[0]))
		return (builtin_handler(cmd, env_val));
	cmd_path = get_cmd_abspath(cmd->args[0], env_val->paths);
	if (!cmd_path)
		cmd_path = ft_strdup(cmd->args[0]);
	if (fork() == 0)
	{
		if (redirect_io(cmd->redi, NULL))
		{
			convert_lst_toenvp(env_val);
			execve(cmd_path, cmd->args, env_val->envp);
			perror(cmd_path);
		}
		exit(1);
	}
	wait(NULL);
	free(cmd_path);
}

void	execute_commands(t_list *cmdlst, t_envval *env_val)
{
	pid_t	*pids;
	size_t	len;
	size_t	i;

	len = ft_lstsize(cmdlst);
	i = 0;
	if (len == 1)
	{
		execute_command(cmdlst->content, env_val);
		return ;
	}
	pids = malloc(sizeof(pid_t) * len);
	while (cmdlst)
	{
		pids[i] = fork();
		if (pids[i++] == 0)
		{
			execute_command(cmdlst->content, env_val);
			exit(1);
		}
		cmdlst = cmdlst->next;
	}
	i = 0;
	while (i < len)
		waitpid(pids[i++], NULL, 0);
	free(pids);
}

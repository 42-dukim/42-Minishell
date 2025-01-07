/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:12:06 by dukim             #+#    #+#             */
/*   Updated: 2025/01/07 17:36:55 by junkwak          ###   ########.fr       */
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
	convert_lst_toenvp(env_val);
	cmd_path = get_cmd_abspath(cmd->args[0], env_val->lst);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		return ;
	}
	if (fork() == 0)
	{
		if (redirect_io(cmd->redi, NULL))
			execve(cmd_path, cmd->args, env_val->envp);
		exit(1);	// 바로 종료가 아닌 main 까지 도달 후에 정상적 종료로 변경?
	}
	wait(NULL);
	free(cmd_path);
}

void	execute_commands(t_list *cmdlst, t_envval *env_val)
{
	pid_t	*pids;
	size_t	len;
	size_t	i;
	int		fd[2];
	int		input_fd = 0;
	int		status;

	len = ft_lstsize(cmdlst);
	if (len == 1)
	{
		execute_command(cmdlst->content, env_val);
		return ;
	}
	i = 0;
	pids = malloc(sizeof(pid_t) * len);
	while (cmdlst)
	{
		pipe(fd);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			dup2(input_fd, STDIN_FILENO);
			if (cmdlst->next)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			execute_command(cmdlst->content, env_val);
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
		sig_all_ign();
		input_fd = fd[0];
		cmdlst = cmdlst->next;
		i++;
	}
	i = 0;
	while (i < len)
	{
		waitpid(pids[i++], &status, 0);
		int	signo = 0;

		if (WIFEXITED(status))
			g_signal = (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			g_signal = WTERMSIG(status) + 128;
		signo = g_signal - 128;
		if (signo == SIGINT)
			printf("^C\n");
		if (signo == SIGQUIT)
			printf("^Quit (core dumped)\n");
	}
	free(pids);
}

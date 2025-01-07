/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:12:06 by dukim             #+#    #+#             */
/*   Updated: 2025/01/07 21:39:53 by junkwak          ###   ########.fr       */
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

static void	handle_externalcmd(t_command *cmd, char *cmd_path, t_bool is_child, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (redirect_io(cmd->redi, fd))
	{
		sig_all_dfl();
		set_terminal(true);
		if (is_child)
			execve(cmd_path, cmd->args, envp);
		pid = fork();
		if (pid == 0)
			execve(cmd_path, cmd->args, envp);
		sig_all_ign();	
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_signal = (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			g_signal = WTERMSIG(status) + 128;
		if (g_signal - 128 == SIGINT)
			printf("^C\n");
		if (g_signal - 128 == SIGQUIT)
			printf("^Quit (core dumped)\n");
	}
	unredirect_io(fd);
}

static int	execute_command(t_command *cmd, t_envval *env_val, t_bool is_child)
{
	char	*cmd_path;

	if (is_builtin_cmd(cmd->args[0]))
		return (builtin_handler(cmd, env_val, is_child));
	convert_lst_toenvp(env_val);
	cmd_path = get_cmd_abspath(cmd->args[0], env_val->lst);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		return (1);
	}
	handle_externalcmd(cmd, cmd_path, is_child, env_val->envp);
	free(cmd_path);
	return (1);
}

static int	execute_pipe(t_list *cmdlst, t_envval *env_val, pid_t *pids, int *fds)
{
	size_t	i;
	int		fd[2];
	int		input_fd;

	i = -1;
	input_fd = 0;
	while (cmdlst)
	{
		pipe(fd);
		fds[++i] = fd[0];
		sig_all_dfl();
		pids[i] = fork();
		if (pids[i] == 0)
		{
			dup2(input_fd, STDIN_FILENO);
			if (cmdlst->next)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execute_command(cmdlst->content, env_val, true);
			return (EXIT_CODE);
		}
		close(fd[1]);
		sig_all_ign();
		input_fd = fd[0];
		cmdlst = cmdlst->next;
	}
	return (1);
}

int	excute_handler(t_list *cmdlst, t_envval *env_val)
{
	pid_t	*pids;
	int		*fds;
	size_t	i;
	size_t	cmdlst_len;
	int		res;
	int		status;

	cmdlst_len = ft_lstsize(cmdlst);
	if (cmdlst_len == 1)
		return (execute_command(cmdlst->content, env_val, false));
	pids = malloc(sizeof(pid_t) * cmdlst_len);
	fds = malloc(sizeof(int) * cmdlst_len);
	res = execute_pipe(cmdlst, env_val, pids, fds);
	if (res)
	{
		i = 0;
		while (i < cmdlst_len)
		{
			waitpid(pids[i], &status, 0);
			close(fds[i]);

			if (WIFEXITED(status))
				g_signal = (WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				g_signal = WTERMSIG(status) + 128;
			i++;
		}
		if (g_signal - 128 == SIGINT)
			printf("^C\n");
		if (g_signal - 128 == SIGQUIT)
			printf("^Quit (core dumped)\n");
	}
	free(fds);
	free(pids);
	return (res);
}

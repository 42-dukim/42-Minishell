/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:32:05 by dukim             #+#    #+#             */
/*   Updated: 2024/11/29 22:32:06 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_global	g_data;

// 명령어의 절대 경로 찾기
char	*get_cmd_abspath(char *cmd)
{
	char	*cmd_path;
	int		i;

	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	cmd = ft_strjoin("/", cmd);
	i = 0;
	while (g_data.path_list[i])
	{
		cmd_path = ft_strjoin(g_data.path_list[i], cmd);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		i++;
	}
	free(cmd);
	if (!g_data.path_list[i])
		return (NULL);
	return (cmd_path);
}

void	parser_handler(char	*line)
{
	t_list	*token_list;
	char	**cmds;
	char	*cmd_path;

	if (!line || line[0] == '\0')
		return ;
	token_list = tokenizer(line);
	cmds = ft_lstto_array(token_list);
	if (!builtin_handler(cmds, g_data.envp))
	{
		cmd_path = get_cmd_abspath(cmds[0]);
		if (cmd_path)
		{
			if (fork() == 0)
				execve(cmd_path, cmds, g_data.envp);
			wait(NULL);
		}
		else
			printf("%s: command not found\n", cmds[0]);
		free(cmd_path);
	}
	ft_freesplit(cmds);
	add_history(line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:23:36 by dukim             #+#    #+#             */
/*   Updated: 2024/12/24 22:23:37 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "command.h"

extern t_global	g_data;

// 명령어의 절대 경로 찾기
char	*get_cmd_abspath(char *cmd, t_list *env_list)
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

void	free_cmd_unit(void *ptr)
{
	t_cmd_unit	*cmd_unit;
	size_t	i;
	
	cmd_unit = (t_cmd_unit *)ptr;
	i = 0;
	while (cmd_unit->cmd->args[i])
		free(cmd_unit->cmd->args[i++]);
	free(cmd_unit->cmd->args);
	free(cmd_unit->cmd->redi);
	free(cmd_unit->cmd);
	free(cmd_unit);
}

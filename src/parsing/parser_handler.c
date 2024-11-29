/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:22:57 by dukim             #+#    #+#             */
/*   Updated: 2024/11/29 22:22:59 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_cmd_physpath(char *cmd, char **env_path)
{
	char	*cmd_path;
	int		i;

	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	cmd = ft_strjoin("/", cmd);
	i = 0;
	while (env_path[i])
	{
		cmd_path = ft_strjoin(env_path[i], cmd);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		i++;
	}
	free(cmd);
	if (!env_path[i])
		return (NULL);
	return (cmd_path);
}

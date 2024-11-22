/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:10:16 by dukim             #+#    #+#             */
/*   Updated: 2024/11/22 21:10:17 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_cmd_path(char *cmd, char **env_path)
{
	char	*cmd_path;
	int		i;

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

char	*get_pathvalue(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

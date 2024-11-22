/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:43:30 by dukim             #+#    #+#             */
/*   Updated: 2024/11/23 00:43:31 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cd(const char *path, const char *home_path)
{
	char	*phys_path;
	char	*curr_path;
	char	*temp;

	if (path[0] == '/')
		phys_path = ft_strdup(path);
	else if (path[0] == '~')
		phys_path = ft_strjoin(home_path, path + 1);
	else
	{
		temp = getcwd(NULL, 0);
		curr_path = ft_strjoin(temp, "/");
		phys_path = ft_strjoin(curr_path, path);
		free(curr_path);
		free(temp);
	}
	if (chdir(phys_path) == -1)
		printf("bash: cd: %s: No such file or directory\n", phys_path);
	free(phys_path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:43:30 by dukim             #+#    #+#             */
/*   Updated: 2024/12/13 17:50:00 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cd(const char *path, const char *home_path)
{
	char	*phys_path;
	char	*old_pwd;
	char	*pwd;

	if (path == NULL)
		return ;
	old_pwd = getcwd(NULL, 0);
	if (path[0] == '~')
		phys_path = ft_strjoin(home_path, path + 1);
	else
		phys_path = ft_strdup(path);
	if (chdir(phys_path) == -1)
		printf("bash: cd: %s: No such file or directory\n", phys_path);
	pwd = getcwd(NULL, 0);
	replace_envvalue("OLDPWD", old_pwd);
	replace_envvalue("PWD", pwd);
	free(old_pwd);
	free(pwd);
	free(phys_path);
}
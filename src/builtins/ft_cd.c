/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:43:30 by dukim             #+#    #+#             */
/*   Updated: 2024/12/15 15:21:39 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cd(const char *path, t_list *env_list)
{
	char	*home_path;
	char	*phys_path;
	char	*old_pwd;
	char	*pwd;

	if (path == NULL)
		return ;
	home_path = ft_getenv("HOME", env_list);
	old_pwd = getcwd(NULL, 0);
	if (path[0] == '~')
		phys_path = ft_strjoin(home_path, path + 1);
	else
		phys_path = ft_strdup(path);
	if (chdir(phys_path) == -1)
		printf("bash: cd: %s: No such file or directory\n", phys_path);
	pwd = getcwd(NULL, 0);
	replace_envvalue("OLDPWD", old_pwd, env_list);
	replace_envvalue("PWD", pwd, env_list);
	free(old_pwd);
	free(pwd);
	free(phys_path);
}

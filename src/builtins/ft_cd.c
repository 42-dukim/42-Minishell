/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:43:30 by dukim             #+#    #+#             */
/*   Updated: 2025/01/05 19:43:55 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	chdir_suc(char *pwd, char *old_pwd, t_list *env_list)
{
	if (getcwd(pwd, sizeof(char) * 1024) == NULL)
	{
		exit(1);
	}
	replace_envvalue("OLDPWD", old_pwd, env_list);
	replace_envvalue("PWD", pwd, env_list);
}

static char	*find_grammer(char **args, t_list *env_list)
{
	char	*way;

	way = args[1];
	if (ft_strncmp(args[1], "-", ft_strlen(args[1])) == 0)
	{
		way = ft_getenv("OLDPWD", env_list);
	}
	else if (ft_strncmp(args[1], "~", ft_strlen(args[1])) == 0)
	{
		way = ft_getenv("HOME", env_list);
	}
	return (way);
}

int	ft_cd(char **path, t_list *env_list)
{
	char	*phys_path;
	char	*old_pwd;
	char	pwd[1024];

	if (path[1] == NULL)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else if (path[2] != NULL)
	{
		ft_putendl_fd("too many argument\n", 2);
		return (1);
	}
	old_pwd = ft_getenv("PWD", env_list);
	phys_path = find_grammer(path, env_list);
	if (chdir(phys_path) == 0)
		chdir_suc(pwd, old_pwd, env_list);
	else
	{
		strerror(errno);
		return (1);
	}
	return (0);
}

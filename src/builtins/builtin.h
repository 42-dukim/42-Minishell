/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:32:16 by dukim             #+#    #+#             */
/*   Updated: 2024/12/26 22:15:36 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BULITIN_H

# include "../../inc/minishell.h"

void	ft_cd(const char *path, t_list *env_list);
void	ft_exit(t_envval *env_val);
void	ft_env(char **cmd, t_list *env_list);
int     ft_export(char **cmds, t_list *env_list);
int		ft_pwd(char **cmds, t_list *env_list);
int		ft_unset(char **cmds, t_list *env_list);

#endif

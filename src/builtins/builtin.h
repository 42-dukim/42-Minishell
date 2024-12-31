/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:32:16 by dukim             #+#    #+#             */
/*   Updated: 2024/12/31 18:59:39 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BULITIN_H

# include "../../inc/minishell.h"

void	ft_cd(const char *path, t_list *env_list);
void	ft_exit(t_envval *env_val);
void	ft_env(char **cmd, t_list *env_list);
void	ft_export(char **cmds, t_envval *env_val);

//작업한파일
int		ft_pwd(t_envval *env_val);
int		ft_unset(char **cmds, t_envval *env_val, int i);//추가함수 int i;
#endif

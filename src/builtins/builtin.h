/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:32:16 by dukim             #+#    #+#             */
/*   Updated: 2025/01/03 17:13:59 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../inc/minishell.h"

void	strerror_exit(void);
void	ft_exit(t_envval *env_val);
//error

//작업한파일
int		ft_cd(char **path, t_list *env_list);
int		ft_export(char **cmds, t_envval *env_val);
int		ft_env(char **cmd, t_list *env_list);
int		ft_pwd(t_envval *env_val);
int		ft_unset(char **cmds, t_envval *env_val, int i);//추가함수 int i;

#endif

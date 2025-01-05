/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:32:16 by dukim             #+#    #+#             */
/*   Updated: 2025/01/05 19:44:49 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../inc/minishell.h"

void	strerror_exit(void);
void	ft_exit(t_envval *env_val);
void	us_handler(t_list *a, t_list *b, t_envval *c, t_env *d);

int		ft_cd(char **path, t_list *env_list);
int		ft_export(char **cmds, t_envval *env_val);
int		ft_env(char **cmd, t_list *env_list);
int		ft_pwd(t_envval *env_val);
int		ft_unset(char **cmds, t_envval *env_val, int i);//추가함수 int i;
int		ft_echo(char **args);

#endif

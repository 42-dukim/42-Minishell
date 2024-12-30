/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:32:16 by dukim             #+#    #+#             */
/*   Updated: 2024/12/26 13:32:17 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BULITIN_H

# include "../../inc/minishell.h"

void	ft_cd(const char *path, t_list *env_list);
void	ft_exit(t_envval *env_val);
void	ft_env(char **cmd, t_list *env_list);
void	ft_export(char **cmds, t_envval *env_val);

#endif

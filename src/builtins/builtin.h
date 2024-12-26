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

void	ft_cd(const char *path, const char *home_path);
void	ft_exit(void);
void	ft_env(char **cmd);
int		ft_export(char **cmds);

#endif

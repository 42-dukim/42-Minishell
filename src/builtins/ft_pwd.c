/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:18:50 by junkwak           #+#    #+#             */
/*   Updated: 2024/12/26 22:13:44 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	ft_pwd(char **cmds, t_list *env_list)
{
	char	*str;
	int	i;

	str = getcwd(NULL,4000);
	printf("%s\n", str);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:50:40 by junkwak           #+#    #+#             */
/*   Updated: 2025/01/05 19:38:53 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "builtin.h"

int	ft_pwd(t_envval *env_val)
{
	char	str[1024];

	(void)env_val;
	if (getcwd(str, sizeof(str)) != NULL)
		printf("%s\n", str);
	else
		strerror_exit();
	return (0);
}

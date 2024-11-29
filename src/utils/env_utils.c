/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:10:16 by dukim             #+#    #+#             */
/*   Updated: 2024/11/22 21:10:17 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_envvalue(char *envp[], const char *env)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(env);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env, len) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

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

extern t_global	g_data;

char	*ft_getenv(const char *env)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(env);
	while (g_data.envp[i])
	{
		if (ft_strncmp(g_data.envp[i], env, len) == 0)
			return (ft_strchr(g_data.envp[i], '=') + 1);
		i++;
	}	
	return (NULL);
}

void	replace_envvalue(const char *env, char	*replace)
{
	int		i;
	size_t	len;
	char	*temp;

	i = 0;
	len = ft_strlen(env);
	while (g_data.envp[i])
	{
		if (ft_strncmp(g_data.envp[i], env, len) == 0)
		{
			temp = g_data.envp[i];
			temp[len + 1] = '\0';
			g_data.envp[i] = ft_strjoin(temp, replace);
			free(temp);
			return ;
		}
		i++;
	}	
}

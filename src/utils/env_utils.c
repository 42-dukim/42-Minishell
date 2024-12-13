/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:10:16 by dukim             #+#    #+#             */
/*   Updated: 2024/12/13 17:35:26 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_global	g_data;

char	*ft_getenv(char *envp[], const char *env)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(env);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env, len) == 0)
			return (ft_strchr(envp[i], '=') + 1);
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

// t_global	*init_env(char **env)
// {
// 	// t_global	*head;
// 	// int	i;

// 	// head = (t_global *)malloc(sizeof(t_global));
// 	// if (!head)
// 	// 	head = NULL;
	
// 	g_data.envp = 
// 	g_data.export = 
	
// }
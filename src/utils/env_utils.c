/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:10:16 by dukim             #+#    #+#             */
/*   Updated: 2024/12/17 20:40:29 by junkwak          ###   ########.fr       */
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
	// t_global	*head;
	// int	i;

	// head = (t_global *)malloc(sizeof(t_global));
	// if (!head)
	// 	head = NULL;
// 	return (0);
// }

// t_list	*env_list(char **envp)
// {
// 	t_list	*head;
// 	t_list	*new_node;
// 	t_list	*temp;
// 	int	i;

// 	head = NULL;
// 	i = 0;
// 	while (envp[i])
// 	{
// 		new_node = (t_list *)malloc(sizeof(t_list));
// 		new_node->content = envp[i];
// 		new_node->next = NULL;
// 		if (!head)
// 			head = new_node;
// 		else
// 		{
// 			temp = head;
// 			while (temp->next)
// 				temp = temp->next;
// 		}
// 		temp->next = new_node;
// 		i++;
// 	}
// 	return (head);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:02:58 by junkwak           #+#    #+#             */
/*   Updated: 2024/12/26 22:14:53 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_unset(char **cmds, t_list *env_list)//성공시 status: 0,실패 : 1
{
	char	*str;
	t_env	*env;
	int	i;
	t_list	*head;
	// if (cmds || cmds[1])
	// 	return (0);
	i = 1;
	
	head = NULL;
	while (cmds[i])
	{
		str = cmds[i];
		head = env_list;
		while (head)
		{
			env = head->content;
			if (env->key == str)
			{
				if (ft_strchr(str,'=') != 0)
					return (0);
				else
				{
					head = NULL;
					head->next = head->next->content;
					env->key = NULL;
					env->value = NULL;
				}
			}
			head = head->next;
		}
		i++;
	}
	return (0);
}

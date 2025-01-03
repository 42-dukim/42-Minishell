// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_unset.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/31 14:51:09 by junkwak           #+#    #+#             */
// /*   Updated: 2024/12/31 15:14:30 by junkwak          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_unset(t_list *head, t_env *env)
{
	free(head);
	free(env->key);
	free(env->value);
}

void	unset_handler(t_list *head, t_list *before_head, t_envval *env_val, t_env *env)
{
	if (head->next && !before_head)
	{
		env_val->lst = env_val->lst->next;
		before_head = head->next;
		free_unset(head, env);
		return ;
	}
	if (head->next)
		before_head->next = head->next;
	else
	{
		before_head->next = NULL;
	}
	free_unset(head, env);
}

int	ft_unset(char **cmds, t_envval *env_val, int i)//성공시 status: 0,실패 : 1
{
	t_env	*env;
	t_list	*before_head;
	t_list	*head;
	char	*str;

	while (cmds[++i])
	{
		str = cmds[i];
		head = env_val->lst;
		while (head)
		{
			env = head->content;
			if (ft_strncmp(env->key, str, ft_strlen(env->key) + 1) == 0)
			{
				if (ft_strchr(cmds[i],'=') != 0)
					return (0);
				unset_handler(head, before_head, env_val, env);
				break ;
			}
			if (head)
				before_head = head;
			head = head->next;
		}
	}
	return (0);
}
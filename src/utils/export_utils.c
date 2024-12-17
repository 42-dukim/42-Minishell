// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   export_utils.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/15 14:50:02 by junkwak           #+#    #+#             */
// /*   Updated: 2024/12/15 15:40:28 by junkwak          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_global	g_data;

void	envp_flag(t_env *env)
{
	t_env   *cur;

	if (env == NULL)
		return ;
	cur = env;
	while (cur)
	{
		if (ft_strncmp(cur->var->content, "_", 1) == 0)
			cur->flag_export = 1;
		cur->flag_env = 0;
		cur = cur->next;
	}
	return ;
}

t_env	*init_env(char **cmds)
{
	t_env	*head;
	int		i;

	head = ft_calloc(0, sizeof(t_env));
	i = -1;
	while (cmds[++i])
	{
		node_back(&head->var,ft_lstnew(cmds[i]));
	}
	return (head);
}

void	set_env(char **cmds)
{
	g_data.link_envp = init_env(g_data.envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:12:12 by dukim             #+#    #+#             */
/*   Updated: 2025/01/06 20:30:54 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(char **args, t_list *env_list)
{
	t_env	*list;
	
	if (args[1])
	{
		// error 출력 필요
		return (127);
	}	
	while (env_list)
	{
		list = env_list->content;
		if (list->value !=NULL)
			printf("%s=%s\n", list->key, list->value);
		env_list = env_list->next;
	}
	return (0);
}

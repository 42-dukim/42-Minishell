/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:12:12 by dukim             #+#    #+#             */
/*   Updated: 2025/01/03 16:42:35 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(char **cmds, t_list *env_list)
{
	size_t	i;
	t_env	*list;
	
	i = 0;
	if (*cmds != NULL)//env 이후 추가명령어 나오면 무조건 에러출력
		return (127);//에러코드 127
	while (env_list)//env 이후 추가명령어 나오면 무조건 에러출력
	{
		list=env_list->content;
		if (list->value !=NULL)
			printf("%s=%s\n", list->key, list->value);
		env_list = env_list->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:12:12 by dukim             #+#    #+#             */
/*   Updated: 2024/12/26 18:12:51 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(char **cmds, t_list *env_list)
{
	size_t	i;
	t_env	*list;
	
	i = 0;
	if (cmds[++i])//env 이후 추가명령어 나오면 무조건 에러출력
	{
		// printf("env : '%s' : No such file or directory\n",cmds[i]);
		print_stderr("env: ", cmds[i]);
		return ;
	}
	while (env_list)//env 이후 추가명령어 나오면 무조건 에러출력
	{
		list=env_list->content;
		if (list->value !=NULL)
			printf("%s=%s\n", list->key, list->value);
		env_list = env_list->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:12:12 by dukim             #+#    #+#             */
/*   Updated: 2024/11/30 02:12:16 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_global	g_data;

void	ft_env(void)
{
	size_t	i;

	i = 0;
	while (g_data.envp[i])
	{
		printf("%s\n", g_data.envp[i]);
		i++;
	}
}

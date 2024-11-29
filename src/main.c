/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:09:53 by dukim             #+#    #+#             */
/*   Updated: 2024/11/22 21:09:54 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_global	g_data;

int	main(char argc, char *argv[], char *envp[])
{
	char	*line;
	char	*cmd_path;
	pid_t	pid;

	enroll_custom_signal();
	g_data.envp = envp;
	g_data.pathvalue = get_envvalue(envp, "PATH");
	g_data.path_list = ft_split(g_data.pathvalue + 5, ':');
	while (1)
	{
		line = readline("minishell$ ");
		parser_handler(line);
		free(line);
	}
	rl_clear_history();
	ft_freesplit(g_data.path_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:09:53 by dukim             #+#    #+#             */
/*   Updated: 2024/12/17 16:50:08 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_global	g_data;

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	*cmd_path;
	pid_t	pid;
	t_list	*env;
	t_list	*export_head;

	enroll_custom_signal();
	g_data.envp = ft_strarrdup(envp);
	set_env(g_data.envp);
	g_data.pathvalue = ft_getenv("PATH");
	g_data.path_list = ft_split(g_data.pathvalue + 5, ':');
	while (1)
	{
		line = readline("minishell$ ");
		parser_handler(line);
		free(line);
	}
	return (0);
}


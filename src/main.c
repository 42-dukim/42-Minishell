/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:09:53 by dukim             #+#    #+#             */
/*   Updated: 2024/12/24 21:04:20 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	*cmd_path;
	t_envval env_val;

	enroll_custom_signal();
	env_val.lst = init_env_list(envp);
	env_val.paths = ft_split(ft_getenv("PATH", env_val.lst), ':');
	env_val.envp = ft_strarrdup(envp);
	env_val.is_changed = false;
	while (1)
	{
		line = readline("minishell$ ");
		parser_handler(line, &env_val);
		free(line);
	}
	return (0);
}


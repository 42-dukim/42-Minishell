/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:09:53 by dukim             #+#    #+#             */
/*   Updated: 2025/01/07 17:33:50 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal;

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_envval	env_val;
	int			res;

	if (!argc || !argv)
		return (0);
	signal_handle_execve();
	env_val.lst = init_env_list(envp);
	env_val.envp = ft_strarrdup(envp);
	env_val.is_changed = false;
	env_val.exit_code = 0;
	while (1)
	{
		g_signal = 0;
		line = readline("minishell$ ");
		if (!line)
			break ;
		parser_handler(line, &env_val);
		free(line);
		if (res == EXIT_CODE)
			break ;
	}
	rl_clear_history();
	ft_lstclear(&env_val.lst, free_env);
	ft_freesplit(env_val.envp);
	return (env_val.exit_code);
}

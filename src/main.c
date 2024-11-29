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

int	main(char argc, char *argv[], char *envp[])
{
	char	*line;
	char	**split;
	char	*pathvalue;
	char	**path_list;
	char	*cmd_path;
	pid_t	pid;

	enroll_custom_signal();
	pathvalue = get_envvalue(envp, "PATH");
	path_list = ft_split(pathvalue + 5, ':');
	while (1)
	{
		line = readline("minishell$ ");
		if (line)
		{
			if (line[0] == '\0')
				continue ;
			split = ft_split(line, ' ');
			cmd_path = get_cmd_path(split[0], path_list);
			if (cmd_path)
			{
				pid = fork();
				if (pid == 0)
					execve(cmd_path, split, envp);
				wait(NULL);
			}
			else
			{
				if (!builtin_handler(split, envp))
					printf("%s: command not found\n", split[0]);
			}
			free(cmd_path);
			ft_freesplit(split);
		}
		else
			break ;
		add_history(line);
		free(line);
	}
	rl_clear_history();
	ft_freesplit(path_list);
}

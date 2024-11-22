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

void	sigint_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("minishell$ \n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(char argc, char *argv[], char *envp[])
{
	char	*line;
	char	**split;
	char	*pathvalue;
	char	**path_list;
	char	*cmd_path;
	pid_t	pid;

	signal(SIGINT, sigint_handler);
	pathvalue = get_pathvalue(envp);
	path_list = ft_split(pathvalue + 5, ':');
	while (1)
	{
		line = readline("minishell$ ");
		if (line)
		{
			if (line[0] == '\0')
				continue ;
			pid = fork();
			if (pid == 0)
			{
				split = ft_split(line, ' ');
				cmd_path = get_cmd_path(split[0], path_list);
				if (cmd_path)
					execve(cmd_path, split, NULL);
				printf("%s: command not found\n", split[0]);
				free(cmd_path);
				ft_freesplit(split);
			}
			else
				wait(NULL);
		}
		else
			break ;
		add_history(line);
		free(line);
	}
	ft_freesplit(path_list);
}

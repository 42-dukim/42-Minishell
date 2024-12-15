// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_echo.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/02 20:50:29 by dukim             #+#    #+#             */
// /*   Updated: 2024/12/02 20:50:30 by dukim            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/minishell.h"

// extern  t_global	g_data;

// void	ft_echo(char **split)
// {
// 	char	**sub_split;
// 	char	**argv;
// 	char	*temp, *envval;
// 	size_t	len;
// 	size_t	i, j;

// 	len = ft_splitlen((const char **)split);
// 	argv = malloc(sizeof(char *) * (len + 1));
// 	i = 0;
// 	while (split[i])
// 	{
// 		if (!ft_strchr(split[i], '$'))
// 		{
// 			argv[i] = ft_strdup(split[i]);
// 			i ++;
// 			continue ;
// 		}
// 		sub_split = ft_split(split[i], '$');
// 		j = 0;
// 		while (sub_split[j])
// 		{
// 			envval = ft_getenv(g_data.envp, sub_split[j]);
// 			if (!envval)
// 			{
// 				argv[i] = ft_strdup("");
// 				j++;
// 				continue; ;
// 			}
// 			if (j == 0)
// 				argv[i] = ft_strdup(envval);
// 			else
// 			{
// 				temp = argv[i];
// 				argv[i] = ft_strjoin(argv[i], envval);
// 				free(temp);
// 			}
// 			j++;
// 		}
// 		ft_freesplit(sub_split);
// 		i++;
// 	}
// 	argv[i] = NULL;
// 	for (int i = 0; argv[i]; i++)
// 		printf("%d: %s\n", i, argv[i]);
// 	if (fork() == 0)
// 		execve("/bin/echo", argv, g_data.envp);
// 	wait(NULL);
// }
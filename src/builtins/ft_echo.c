/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:50:29 by dukim             #+#    #+#             */
/*   Updated: 2025/01/07 02:46:17 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_newlineoption(char **args, int *i)
{
	int	j;
	int newline;
	int flag;
	
	flag = 0;
	newline = 0;
	while (args[++*i])
	{
		if (args[*i][0] != '-')
			break ;
		j = 0;
		while (args[*i][++j])
		{
			if (args[*i][j] == 'n')
				newline = 1;
			else
			{
				newline = 0;
				i -= 1;
				break ;
			}
		}
		if (newline == 1)
			flag++;
		if (newline == 0)
			break ;
	}
	if (flag > 0)
		newline = 1;
	return (newline);
}


static void	echo_grammer(char **args)
{
	int	newline;
	int	i;

	if (args == NULL || args[0] == NULL)
		return ;
	i = 0;
	newline = is_newlineoption(args, &i);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		if (!args[i + 1])
		{
			if (newline == 0)
				printf("\n");
		}
		i++;
	}
	return ;
}

int	ft_echo(char **args)
{
	if (args == NULL || args[0] == NULL)
		return (0);
	if (args[1] != NULL)
		echo_grammer(args);
	return (0);
}

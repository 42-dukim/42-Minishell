/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:50:29 by dukim             #+#    #+#             */
/*   Updated: 2024/12/02 20:50:30 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo_print(char **args, int result, int i)
{
	if (result == 1)
	{
		while (args[i])
		{
			printf("%s", args[i]);
			if (!args[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
		return (0);
	}
	else if (result == 2)
		return (0);
	else if (result == 0)
	{
		while (args[++i])
			printf("%s", args[i]);
		printf("\n");
		return (0);
	}
	printf("\n");
	return (0);
}

int	echo_grammer(char *args)
{
	int	result;
	int	count;

	count = 0;
	result = 0;
	if (*args != '-')
		return (result);
	result += 1;
	args++;
	while (*args)
	{
		if (*args != 'n')
			return (result);
		args++;
		count++;
	}
	if (count != 0)
		result += 1;
	return (result);
}

int	ft_echo(char **args)
{
	int	i;
	int	result;

	i = 0;
	if (args == NULL || args[0] == NULL)
		return (0);
	if (args[2] == 0 && args[1] != NULL)
		result = echo_grammer(args[1]);
	echo_print(args, result, i);
	return (0);
}

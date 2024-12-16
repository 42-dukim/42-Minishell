/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolla_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:47:30 by dukim             #+#    #+#             */
/*   Updated: 2024/12/06 19:47:31 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_bool	is_dollar_separator(char ch)
{
	if (ch == ' ' || ch == '\'' || ch == '"' || ch == '$')
		return (true);
	return (false);
}

size_t	dollar_parser(char **token, char *new)
{	
	char	*envvalue;
	char	*dollar;
	size_t	i;

	(*token)++;
	dollar = ft_calloc(sizeof(char), ft_strlen(*token) + 1);
	i = 0;
	while (!is_dollar_separator(**token) && **token)
	{
		dollar[i] = **token;
		i++;
		(*token)++;
	}
	if (i == 0)
	{
		free(dollar);
		return (0);
	}
	envvalue = ft_getenv(dollar);
	free(dollar);
	if (envvalue)
		return (ft_strlcpy(new, envvalue, ft_strlen(envvalue) + 1));
	return (0);
}
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
	if (ch == ' ' || ch == '\'' || ch == '$')
		return (true);
	return (false);
}

static char	*get_dollar_token(char *token, size_t *i)
{
	char	*dollar_token;
	char	*envvalue;
	char	*dollar;
	size_t	ii;

	dollar_token = token;
	dollar = ft_calloc(sizeof(char), ft_strlen(dollar_token) + 1);
	ii = ++(*i);
	while (!is_dollar_separator(dollar_token[*i]) && dollar_token[*i])
	{
		dollar[*i - ii] = dollar_token[*i];
		(*i)++;
	}
	if (*i > ii)
	{
		envvalue = ft_getenv(dollar);
		if (envvalue)
		{
			dollar_token = ft_strreplace(dollar_token, ii, *i, envvalue);
			*i += (ft_strlen(envvalue) - (*i - ii + 1));
		}
		else
		{
			ft_strsplice(dollar_token, ii - 1, *i - 1);
			*i = ii - 1;
		}
	}
	free(dollar);
	return (dollar_token);
}

char	*dollar_parser(char *token)
{	
	size_t	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			token = get_dollar_token(token, &i);
			continue ;
		}
		i++;
	}
	return (token);
}
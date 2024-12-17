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

void	dollar_parser(t_word *word, char *pre, size_t *i)
{	
	char	*dollar;
	char	*envvalue;
	size_t	j;

	(*i)++;
	dollar = ft_calloc(sizeof(char), ft_strlen(pre + *i) + 1);
	j = 0;
	while (!is_dollar_separator(pre[*i]) && pre[*i])
	{
		dollar[j] = pre[*i];
		j++;
		(*i)++;
	}
	if (j == 0)
	{
		free(dollar);
		return ;
	}
	envvalue = ft_getenv(dollar);
	free(dollar);
	if (envvalue)
		append_str_inword(word, envvalue);
	(*i)--;
}
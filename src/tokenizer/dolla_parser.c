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

#include "tokenizer.h"

static t_bool	is_dollar_separator(char ch)
{
	if (ch == ' ' || ch == '\'' || ch == '"' || ch == '$')
		return (true);
	return (false);
}

static	size_t	get_dollarvalue(t_word *word, char *pre, t_envval *env_val)
{
	char	*dollar;
	char	*envvalue;
	size_t	i;

	if (*pre == '?')
	{
		envvalue = ft_itoa(env_val->exit_code);
		append_str_inword(word, envvalue);
		free(envvalue);
		return (0);
	}
	dollar = ft_calloc(sizeof(char), ft_strlen(pre) + 1);
	i = 0;
	while (!is_dollar_separator(*pre) && *pre)
		dollar[i++] = *pre++;
	if (i == 0)
		return (0);
	envvalue = ft_getenv(dollar, env_val->lst);
	if (envvalue)
		append_str_inword(word, envvalue);
	free(dollar);
	return (i - 1);
}

void	dollar_parser(t_word *word, t_envval *env_val)
{	
	char	*pre;
	size_t	i;

	if (!word->is_dollar)
		return ;
	pre = word->content;
	init_word(word);
	i = -1;
	while (pre[++i])
	{
		if (pre[i] == '$')
		{
			i++;
			i += get_dollarvalue(word, pre + i, env_val);
			continue ;
		}
		append_ch_inword(word, pre[i]);
	}
	free(pre);
}

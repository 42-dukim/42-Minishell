/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:20:14 by dukim             #+#    #+#             */
/*   Updated: 2024/12/16 20:20:15 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#define TOKEN_LEN 64

void	init_token(t_token *token)
{
	token->idx = 0;
	token->max_len = TOKEN_LEN;
	token->content = ft_calloc(sizeof(char), TOKEN_LEN + 1);
}

void	append_ch_intoken(t_token *token, char ch)
{
	char	*extend;

	if (token->idx == token->max_len)
	{
		token->max_len *= 2;
		extend = ft_calloc(sizeof(char), token->max_len + 1);
		ft_strlcpy(extend, token->content, token->max_len / 2 + 1);
		free(token->content);
		token->content = extend;
	}
	token->content[token->idx++] = ch;
}

void	append_str_intoken(t_token *token, char *str)
{
	while (*str)
	{
		append_ch_intoken(token, *str);
		str++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:36:23 by dukim             #+#    #+#             */
/*   Updated: 2024/12/13 19:36:24 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	void	convert_tokencotent(t_token *token)
{
	char	*pre;
	char	quote;
	size_t	i;

	pre = token->content;
	init_token(token);
	quote = 0;
	i = -1;
	while(pre[++i])
	{
		if (is_quote_ch(pre[i]))
		{
			if (quote == 0)
				quote = pre[i];
			else if (quote == pre[i])
				quote = 0;
			else
				append_ch_intoken(token, pre[i]);
		}
		else if (pre[i] == '$' && quote != '\'')
			dollar_parser(token, pre, &i);
		else
			append_ch_intoken(token, pre[i]);
	}
	free(pre);
}

static int	specitalch_handler(t_list **token_list, char **line, t_token *token)
{
	if (is_quote_ch(**line))
	{
		quote_parser(line, token);
		if (!token->content)
			return (-1);
	}
	else if (**line == ' ')
	{
		if (token->idx == 0)
			return (true);
		convert_tokencotent(token);
		ft_lstadd_back(token_list, ft_lstnew(token->content));
		init_token(token);
	}
	else
		return (1);
	return (0);
}

t_list	*tokenizer(char *line)
{
	t_list	*token_list;
	t_token	*token;
	int		res;

	token_list = NULL;
	token = malloc(sizeof(t_token) * 1);
	init_token(token);
	while (*line)
	{
		res = specitalch_handler(&token_list, &line, token);
		if (res == -1)
		{
			ft_lstclear(&token_list, free);
			break ;
		}
		if (res == 1)
			append_ch_intoken(token, *line);
		line++;
	}
	if (token->idx > 0)
	{
		convert_tokencotent(token);
		ft_lstadd_back(&token_list, ft_lstnew(token->content));
	}
	else
		free(token->content);
	free(token);
	return (token_list);
}
